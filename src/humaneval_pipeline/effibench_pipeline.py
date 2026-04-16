from __future__ import annotations

import ast
import json
import platform
import re
import shutil
import subprocess
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any, Iterable

from .artifact_paths import (
    baseline_code_path,
    cleaned_code_path,
    evaluation_path,
    generation_metadata_path,
    prompt_path,
    raw_json_response_path,
    raw_text_response_path,
)
from .config import ExperimentConfig, load_config
from .effibench_official import (
    read_effibench_dat_metrics,
    run_official_effibench_evaluator,
    stage_effibench_results,
    summarize_official_effibench_results,
    write_effibench_summary,
)
from .logging_utils import configure_logging
from .model_client import OpenAIModelClient
from .response_cleaner import clean_model_response
from .utils import (
    make_relative,
    read_json,
    read_jsonl,
    sanitize_task_id,
    write_csv,
    write_json,
    write_text,
)

STAGE_NAMES = ("prepare", "generate", "evaluate", "aggregate")

PROMPT_TEMPLATES = {
    "minimal": {
        "runtime": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for runtime while preserving correctness. Keep the interface used by the test "
            "cases unchanged. Output only the final Python code in a single ```python``` block. Do "
            "not include the provided test cases in your answer."
        ),
        "memory": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for memory usage while preserving correctness. Keep the interface used by the "
            "test cases unchanged. Output only the final Python code in a single ```python``` block. "
            "Do not include the provided test cases in your answer."
        ),
        "balanced": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for both runtime and memory usage while preserving correctness. Balance the "
            "tradeoff between them and keep the interface used by the test cases unchanged. Output "
            "only the final Python code in a single ```python``` block. Do not include the provided "
            "test cases in your answer."
        ),
    },
    "detailed": {
        "runtime": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for runtime while preserving correctness. Prefer better asymptotic complexity, "
            "reduce repeated work, use efficient data structures, and avoid unnecessary overhead. "
            "Keep the interface used by the test cases unchanged. Output only the final Python code "
            "in a single ```python``` block. Do not include the provided test cases in your answer."
        ),
        "memory": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for memory usage while preserving correctness. Avoid unnecessary auxiliary "
            "containers, copying, and temporary allocations; reuse storage when reasonable. Keep the "
            "interface used by the test cases unchanged. Output only the final Python code in a "
            "single ```python``` block. Do not include the provided test cases in your answer."
        ),
        "balanced": (
            "Write a Python Solution class that solves the task and passes the provided test cases. "
            "Optimize for both runtime and memory usage while preserving correctness. Favor efficient "
            "algorithms, avoid repeated work, and reduce unnecessary allocations without making one "
            "metric much worse to improve the other. Keep the interface used by the test cases "
            "unchanged. Output only the final Python code in a single ```python``` block. Do not "
            "include the provided test cases in your answer."
        ),
    },
}

RAW_FIELDNAMES = [
    "task_id",
    "task_name",
    "difficulty",
    "language",
    "objective",
    "prompt_detail",
    "variant",
    "success",
    "runtime_seconds",
    "max_memory_mb",
    "memory_usage_mb_seconds",
    "source_path",
    "dat_path",
]

SUMMARY_FIELDNAMES = [
    "task_id",
    "task_name",
    "difficulty",
    "language",
    "objective",
    "prompt_detail",
    "correctness_before",
    "correctness_after",
    "runtime_before_mean_ms",
    "runtime_after_mean_ms",
    "memory_before_mean",
    "memory_after_mean",
    "memory_area_before_mean",
    "memory_area_after_mean",
    "runtime_improvement_ratio",
    "memory_improvement_ratio",
    "memory_area_improvement_ratio",
    "compile_error",
    "test_error",
    "timeout",
    "compile_error_before",
    "compile_error_after",
    "test_error_before",
    "test_error_after",
    "timeout_before",
    "timeout_after",
    "runtime_before_std_ms",
    "runtime_after_std_ms",
    "runtime_before_cv",
    "runtime_after_cv",
    "memory_before_std",
    "memory_after_std",
    "memory_before_cv",
    "memory_after_cv",
    "baseline_code_path",
    "raw_response_path",
    "raw_response_json_path",
    "cleaned_code_path",
    "prompt_path",
    "signature_valid",
    "model_name",
    "from_cache",
    "official_results_json_path",
    "official_summary_json_path",
]


@dataclass(frozen=True)
class EffiBenchTask:
    task_id: str
    task_name: str
    difficulty: str | None
    language: str
    description: str
    markdown_description: str
    canonical_solution: str
    small_test_cases: str
    test_case: str
    entry_point: str

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)

    @classmethod
    def from_dict(cls, payload: dict[str, Any]) -> "EffiBenchTask":
        return cls(
            task_id=str(payload["task_id"]),
            task_name=str(payload["task_name"]),
            difficulty=(
                str(payload["difficulty"])
                if payload.get("difficulty") not in (None, "")
                else None
            ),
            language=str(payload["language"]),
            description=str(payload["description"]),
            markdown_description=str(payload["markdown_description"]),
            canonical_solution=str(payload["canonical_solution"]),
            small_test_cases=str(payload["small_test_cases"]),
            test_case=str(payload["test_case"]),
            entry_point=str(payload["entry_point"]),
        )


def run_effibench_pipeline(config_path: str | Path, stages: Iterable[str] | None = None) -> None:
    config = load_config(config_path)
    if config.language != "python":
        raise ValueError(
            f"EffiBench pipeline currently requires language=python, got {config.language!r}."
        )

    logger = configure_logging(config.resolve_path(config.paths.logs_dir) / "effibench_pipeline.log")
    selected_stages = tuple(stages or STAGE_NAMES)
    invalid = set(selected_stages) - set(STAGE_NAMES)
    if invalid:
        raise ValueError(f"Unsupported pipeline stages: {sorted(invalid)}")

    logger.info("Running EffiBench pipeline stages: %s", ", ".join(selected_stages))
    tasks: list[EffiBenchTask]

    if "prepare" in selected_stages:
        tasks = _prepare(config, logger)
    else:
        tasks = _load_selected_manifest(config)

    if "generate" in selected_stages:
        _generate(config, tasks, logger)

    if "evaluate" in selected_stages:
        _evaluate(config, tasks, logger)

    if "aggregate" in selected_stages:
        raw_path, summary_path = write_effibench_aggregated_results(config, tasks)
        logger.info("Wrote EffiBench raw CSV to %s", raw_path)
        logger.info("Wrote EffiBench summary CSV to %s", summary_path)


def load_effibench_tasks(config: ExperimentConfig) -> list[EffiBenchTask]:
    dataset_path = config.resolve_path(config.dataset_path)
    if not dataset_path.exists():
        raise FileNotFoundError(f"Dataset file does not exist: {dataset_path}")

    if dataset_path.suffix == ".jsonl":
        payload = read_jsonl(dataset_path)
    else:
        payload = json.loads(dataset_path.read_text(encoding="utf-8"))

    if not isinstance(payload, list):
        raise ValueError("EffiBench dataset must contain a JSON array or JSONL sequence of task objects.")

    tasks = [_build_effibench_task(row) for row in payload]
    return _select_tasks(
        tasks,
        config.selected_task_ids,
        config.selected_difficulty_levels,
        config.max_tasks,
    )


def write_effibench_aggregated_results(
    config: ExperimentConfig,
    tasks: list[EffiBenchTask],
) -> tuple[Path, Path]:
    root = config.project_root
    raw_rows: list[dict[str, Any]] = []
    summary_rows: list[dict[str, Any]] = []

    for task in tasks:
        before_result = read_json(evaluation_path(config, "baseline", task.task_id, task.language))
        raw_rows.append(_measurement_row(task, before_result, root))

        for objective in config.objectives:
            for prompt_detail in config.prompt_detail_levels:
                after_result = read_json(
                    evaluation_path(
                        config,
                        "optimized",
                        task.task_id,
                        task.language,
                        objective,
                        prompt_detail,
                    )
                )
                generation_record = read_json(
                    generation_metadata_path(config, task.task_id, task.language, objective, prompt_detail)
                )
                raw_rows.append(_measurement_row(task, after_result, root))
                summary_rows.append(
                    _summary_row(
                        config=config,
                        task=task,
                        objective=objective,
                        prompt_detail=prompt_detail,
                        before_result=before_result,
                        after_result=after_result,
                        generation_record=generation_record,
                    )
                )

    raw_path = config.resolve_path(config.paths.raw_runs_csv)
    summary_path = config.resolve_path(config.paths.summary_csv)
    write_csv(raw_path, raw_rows, RAW_FIELDNAMES)
    write_csv(summary_path, summary_rows, SUMMARY_FIELDNAMES)
    return raw_path, summary_path


def _prepare(config: ExperimentConfig, logger) -> list[EffiBenchTask]:
    tasks = load_effibench_tasks(config)
    _save_selected_manifest(config, tasks)

    for task in tasks:
        write_text(baseline_code_path(config, task.task_id, task.language), task.canonical_solution)

    write_json(config.resolve_path(config.paths.run_manifest), _build_run_manifest(config, tasks))
    logger.info("Prepared %s EffiBench tasks from %s", len(tasks), config.dataset_path)
    return tasks


def _generate(config: ExperimentConfig, tasks: list[EffiBenchTask], logger) -> None:
    client = OpenAIModelClient(config)
    for task in tasks:
        for objective in config.objectives:
            for prompt_detail in config.prompt_detail_levels:
                prompt = build_effibench_prompt(task, objective, prompt_detail)
                prompt_file = prompt_path(config, task.task_id, task.language, objective, prompt_detail)
                raw_text_path = raw_text_response_path(
                    config, task.task_id, task.language, objective, prompt_detail
                )
                raw_json_path = raw_json_response_path(
                    config, task.task_id, task.language, objective, prompt_detail
                )
                cleaned_path = cleaned_code_path(
                    config, task.task_id, task.language, objective, prompt_detail
                )
                metadata_path = generation_metadata_path(
                    config, task.task_id, task.language, objective, prompt_detail
                )

                write_text(prompt_file, prompt)
                model_result = client.generate(prompt)
                write_text(raw_text_path, model_result.raw_text)
                write_json(raw_json_path, model_result.response_json)

                cleaned = clean_model_response(
                    model_result.raw_text,
                    task.canonical_solution,
                    task.entry_point,
                    task.language,
                )
                write_text(cleaned_path, cleaned.cleaned_code)
                write_json(
                    metadata_path,
                    {
                        "task_id": task.task_id,
                        "task_name": task.task_name,
                        "language": task.language,
                        "objective": objective,
                        "prompt_detail": prompt_detail,
                        "prompt_path": make_relative(prompt_file, config.project_root),
                        "raw_text_path": make_relative(raw_text_path, config.project_root),
                        "raw_json_path": make_relative(raw_json_path, config.project_root),
                        "cleaned_code_path": make_relative(cleaned_path, config.project_root),
                        "cache_key": model_result.cache_key,
                        "signature_valid": cleaned.signature_valid,
                        "cleaner_notes": cleaned.notes,
                        "model_name": config.model.name,
                        "from_cache": model_result.from_cache,
                    },
                )
                logger.info(
                    "Generated EffiBench solution | %s | %s | %s | cache=%s",
                    task.task_id,
                    objective,
                    prompt_detail,
                    model_result.from_cache,
                )


def _evaluate(config: ExperimentConfig, tasks: list[EffiBenchTask], logger) -> None:
    effibench_root = _find_effibench_root(config.resolve_path(config.dataset_path))
    python_executable = config.resolve_executable(config.toolchain.python_executable)

    for objective in config.objectives:
        for prompt_detail in config.prompt_detail_levels:
            model_label = _model_label(config.model.name, objective, prompt_detail)
            official_input_path = _official_input_path(config, objective, prompt_detail, model_label)
            official_summary_path = _official_summary_path(config, objective, prompt_detail, model_label)
            official_stdout_path = _official_stdout_path(config, objective, prompt_detail, model_label)
            official_stderr_path = _official_stderr_path(config, objective, prompt_detail, model_label)

            rows = []
            for task in tasks:
                metadata = read_json(
                    generation_metadata_path(config, task.task_id, task.language, objective, prompt_detail)
                )
                cleaned_path = config.project_root / metadata["cleaned_code_path"]
                completion = cleaned_path.read_text(encoding="utf-8") if cleaned_path.exists() else ""
                rows.append(
                    {
                        "problem_idx": int(task.task_id),
                        "task_name": task.task_name,
                        "description": task.description,
                        "markdown_description": task.markdown_description,
                        "canonical_solution": task.canonical_solution,
                        "small_test_cases": task.small_test_cases,
                        "test_case": task.test_case,
                        "completion": completion,
                    }
                )

            write_json(official_input_path, rows)
            stage_effibench_results(
                input_json=official_input_path,
                effibench_root=effibench_root,
                model_name=model_label,
            )

            if config.overwrite_existing or not official_summary_path.exists():
                completed = run_official_effibench_evaluator(
                    effibench_root=effibench_root,
                    model_name=model_label,
                    python_executable=python_executable,
                )
                write_text(official_stdout_path, completed.stdout)
                write_text(official_stderr_path, completed.stderr)
                summary = summarize_official_effibench_results(
                    effibench_root=effibench_root,
                    model_name=model_label,
                    num_tasks_requested=len(tasks),
                )
                write_effibench_summary(summary, official_summary_path)
                logger.info(
                    "Evaluated EffiBench condition via official evaluator | %s | %s",
                    objective,
                    prompt_detail,
                )
            else:
                logger.info(
                    "Skipped official EffiBench evaluator because summary already exists | %s | %s",
                    objective,
                    prompt_detail,
                )

            _write_canonical_evaluations(config, tasks, effibench_root, config.overwrite_existing)
            _write_condition_evaluations(
                config=config,
                tasks=tasks,
                objective=objective,
                prompt_detail=prompt_detail,
                model_label=model_label,
                effibench_root=effibench_root,
                official_input_path=official_input_path,
                official_summary_path=official_summary_path,
            )


def _write_canonical_evaluations(
    config: ExperimentConfig,
    tasks: list[EffiBenchTask],
    effibench_root: Path,
    overwrite_existing: bool,
) -> None:
    canonical_dir = effibench_root / "dat_results" / "canonical_solution"
    for task in tasks:
        eval_path = evaluation_path(config, "baseline", task.task_id, task.language)
        if eval_path.exists() and not overwrite_existing:
            continue
        dat_path = canonical_dir / f"{task.task_id}.dat"
        write_json(
            eval_path,
            _evaluation_payload(
                task,
                dat_path,
                "before",
                None,
                None,
                config.project_root,
                source_path=baseline_code_path(config, task.task_id, task.language),
            ),
        )


def _write_condition_evaluations(
    config: ExperimentConfig,
    tasks: list[EffiBenchTask],
    objective: str,
    prompt_detail: str,
    model_label: str,
    effibench_root: Path,
    official_input_path: Path,
    official_summary_path: Path,
) -> None:
    dat_dir = effibench_root / "dat_results" / model_label
    for task in tasks:
        eval_path = evaluation_path(
            config,
            "optimized",
            task.task_id,
            task.language,
            objective,
            prompt_detail,
        )
        metadata = read_json(
            generation_metadata_path(config, task.task_id, task.language, objective, prompt_detail)
        )
        source_path = config.project_root / metadata["cleaned_code_path"]
        write_json(
            eval_path,
            _evaluation_payload(
                task=task,
                dat_path=dat_dir / f"{task.task_id}.dat",
                variant="after",
                objective=objective,
                prompt_detail=prompt_detail,
                project_root=config.project_root,
                source_path=source_path,
                official_input_path=official_input_path,
                official_summary_path=official_summary_path,
            ),
        )


def _evaluation_payload(
    task: EffiBenchTask,
    dat_path: Path,
    variant: str,
    objective: str | None,
    prompt_detail: str | None,
    project_root: Path,
    source_path: Path | None = None,
    official_input_path: Path | None = None,
    official_summary_path: Path | None = None,
) -> dict[str, Any]:
    exists = dat_path.exists()
    runtime_mean_ms = None
    memory_mean = None
    memory_area_mean = None
    sample: dict[str, Any] | None = None
    if exists:
        metrics = read_effibench_dat_metrics(dat_path)
        runtime_mean_ms = metrics.runtime_seconds * 1000.0
        memory_mean = metrics.max_memory_mb
        memory_area_mean = metrics.memory_usage_mb_seconds
        sample = {
            "repetition_index": 1,
            "runtime_milliseconds": runtime_mean_ms,
            "peak_memory_bytes": int(round(metrics.max_memory_mb * 1024 * 1024)),
            "returncode": 0,
            "stdout": "",
            "stderr": "",
        }

    actual_source_path = source_path or Path(task.task_id)
    return {
        "task_id": task.task_id,
        "task_name": task.task_name,
        "language": task.language,
        "variant": variant,
        "objective": objective,
        "prompt_detail": prompt_detail,
        "source_path": str(actual_source_path),
        "correctness_pass": bool(exists),
        "compile_error": False,
        "test_error": not exists,
        "timeout": False,
        "compile_stdout": "",
        "compile_stderr": "",
        "compile_returncode": None,
        "correctness_stdout": "",
        "correctness_stderr": "" if exists else "EffiBench official evaluator did not produce a dat file.",
        "correctness_returncode": 0 if exists else 1,
        "runtime_mean_ms": runtime_mean_ms,
        "runtime_std_ms": 0.0 if exists else None,
        "runtime_cv": 0.0 if exists and runtime_mean_ms else None,
        "memory_mean": memory_mean,
        "memory_std": 0.0 if exists and memory_mean is not None else None,
        "memory_cv": 0.0 if exists and memory_mean else None,
        "memory_area_mean": memory_area_mean,
        "samples": [sample] if sample is not None else [],
        "dat_path": make_relative(dat_path, project_root),
        "official_results_json_path": (
            make_relative(official_input_path, project_root) if official_input_path else ""
        ),
        "official_summary_json_path": (
            make_relative(official_summary_path, project_root) if official_summary_path else ""
        ),
    }


def build_effibench_prompt(task: EffiBenchTask, objective: str, prompt_detail: str) -> str:
    instruction = PROMPT_TEMPLATES[prompt_detail][objective]
    description = task.markdown_description.strip() or task.description.strip()
    return (
        f"{instruction}\n\n"
        f"# Task description\n```python\n{description}\n```\n\n"
        f"# Test cases\n```python\n{task.small_test_cases.strip()}\n```\n"
    )


def _build_effibench_task(row: Any) -> EffiBenchTask:
    if not isinstance(row, dict):
        raise ValueError(f"EffiBench dataset row must be an object, got {type(row).__name__}.")

    required = [
        "problem_idx",
        "task_name",
        "description",
        "markdown_description",
        "canonical_solution",
        "small_test_cases",
        "test_case",
    ]
    missing = [field for field in required if field not in row]
    if missing:
        raise KeyError(
            f"EffiBench dataset row is missing fields {missing}. Available fields: {sorted(row.keys())}"
        )

    canonical_solution = str(row["canonical_solution"])
    entry_point = _extract_entry_point(canonical_solution, str(row["small_test_cases"]))
    return EffiBenchTask(
        task_id=str(row["problem_idx"]),
        task_name=str(row["task_name"]),
        difficulty=(
            str(row["difficulty"]).strip()
            if row.get("difficulty") not in (None, "")
            else None
        ),
        language="python",
        description=str(row["description"]),
        markdown_description=str(row["markdown_description"]),
        canonical_solution=canonical_solution,
        small_test_cases=str(row["small_test_cases"]),
        test_case=str(row["test_case"]),
        entry_point=entry_point,
    )


def _extract_entry_point(canonical_solution: str, small_test_cases: str) -> str:
    for line in small_test_cases.splitlines():
        match = re.search(r"\bsolution\.([A-Za-z_][A-Za-z0-9_]*)\s*\(", line)
        if match:
            return match.group(1)

    try:
        module = ast.parse(canonical_solution)
    except SyntaxError:
        module = None

    if module is not None:
        for node in module.body:
            if not isinstance(node, ast.ClassDef) or node.name != "Solution":
                continue
            public_methods = [
                member.name
                for member in node.body
                if isinstance(member, (ast.FunctionDef, ast.AsyncFunctionDef))
                and not member.name.startswith("_")
            ]
            if public_methods:
                return public_methods[0]

            any_methods = [
                member.name
                for member in node.body
                if isinstance(member, (ast.FunctionDef, ast.AsyncFunctionDef))
            ]
            if any_methods:
                return any_methods[0]

    for line in canonical_solution.splitlines():
        stripped = line.strip()
        if stripped.startswith("def ") and "(" in stripped:
            return stripped[len("def ") : stripped.index("(")].strip()

    raise ValueError("Could not infer EffiBench entry point from canonical solution or small test cases.")


def _select_tasks(
    tasks: list[EffiBenchTask],
    selected_task_ids: list[str],
    selected_difficulty_levels: list[str],
    max_tasks: int | None,
) -> list[EffiBenchTask]:
    sorted_tasks = sorted(tasks, key=lambda task: _sort_key(task.task_id))
    filtered_tasks = sorted_tasks

    if selected_difficulty_levels:
        available_levels = sorted(
            {task.difficulty for task in sorted_tasks if task.difficulty},
            key=str.casefold,
        )
        if not available_levels:
            raise ValueError(
                "Difficulty filtering was requested, but the EffiBench dataset does not include a difficulty field."
            )

        normalized_available = {_normalize_difficulty(level) for level in available_levels}
        normalized_requested = {_normalize_difficulty(level) for level in selected_difficulty_levels}
        missing_levels = sorted(normalized_requested - normalized_available, key=str.casefold)
        if missing_levels:
            raise ValueError(
                "Requested difficulty levels are not present in the EffiBench dataset: "
                f"{missing_levels}. Available levels: {available_levels}"
            )

        filtered_tasks = [
            task
            for task in filtered_tasks
            if task.difficulty and _normalize_difficulty(task.difficulty) in normalized_requested
        ]

    if not selected_task_ids:
        if max_tasks is None:
            return filtered_tasks
        return filtered_tasks[:max_tasks]

    selected_ids = {str(task_id) for task_id in selected_task_ids}
    filtered = [task for task in filtered_tasks if task.task_id in selected_ids]
    missing = sorted(selected_ids - {task.task_id for task in filtered}, key=_sort_key)
    if missing:
        scope = "filtered EffiBench task set"
        if selected_difficulty_levels:
            scope += f" for difficulty levels {selected_difficulty_levels}"
        raise ValueError(f"Selected task IDs not found in {scope}: {missing}")
    return filtered


def _save_selected_manifest(config: ExperimentConfig, tasks: list[EffiBenchTask]) -> None:
    write_json(
        config.resolve_path(config.paths.selected_tasks_manifest),
        {
            "benchmark": "effibench",
            "language": config.language,
            "dataset_path": config.dataset_path,
            "selected_task_ids": [task.task_id for task in tasks],
            "selected_difficulty_levels": config.selected_difficulty_levels,
            "max_tasks": config.max_tasks,
            "tasks": [task.to_dict() for task in tasks],
        },
    )


def _load_selected_manifest(config: ExperimentConfig) -> list[EffiBenchTask]:
    manifest_path = config.resolve_path(config.paths.selected_tasks_manifest)
    if not manifest_path.exists():
        raise FileNotFoundError(
            "Selected EffiBench task manifest not found. Run the prepare stage first or include it in --stages."
        )
    payload = read_json(manifest_path)
    return [EffiBenchTask.from_dict(task_payload) for task_payload in payload["tasks"]]


def _measurement_row(task: EffiBenchTask, result: dict[str, Any], root: Path) -> dict[str, Any]:
    return {
        "task_id": task.task_id,
        "task_name": task.task_name,
        "difficulty": task.difficulty or "",
        "language": result["language"],
        "objective": result.get("objective") or "",
        "prompt_detail": result.get("prompt_detail") or "",
        "variant": result["variant"],
        "success": int(bool(result["correctness_pass"])),
        "runtime_seconds": _ms_to_seconds(result.get("runtime_mean_ms")),
        "max_memory_mb": result.get("memory_mean"),
        "memory_usage_mb_seconds": result.get("memory_area_mean"),
        "source_path": make_relative(Path(result["source_path"]), root),
        "dat_path": result.get("dat_path", ""),
    }


def _summary_row(
    config: ExperimentConfig,
    task: EffiBenchTask,
    objective: str,
    prompt_detail: str,
    before_result: dict[str, Any],
    after_result: dict[str, Any],
    generation_record: dict[str, Any],
) -> dict[str, Any]:
    runtime_before_mean_ms = before_result.get("runtime_mean_ms")
    runtime_after_mean_ms = after_result.get("runtime_mean_ms")
    memory_before_mean = before_result.get("memory_mean")
    memory_after_mean = after_result.get("memory_mean")
    memory_area_before = before_result.get("memory_area_mean")
    memory_area_after = after_result.get("memory_area_mean")

    return {
        "task_id": task.task_id,
        "task_name": task.task_name,
        "difficulty": task.difficulty or "",
        "language": task.language,
        "objective": objective,
        "prompt_detail": prompt_detail,
        "correctness_before": int(bool(before_result.get("correctness_pass"))),
        "correctness_after": int(bool(after_result.get("correctness_pass"))),
        "runtime_before_mean_ms": runtime_before_mean_ms,
        "runtime_after_mean_ms": runtime_after_mean_ms,
        "memory_before_mean": memory_before_mean,
        "memory_after_mean": memory_after_mean,
        "memory_area_before_mean": memory_area_before,
        "memory_area_after_mean": memory_area_after,
        "runtime_improvement_ratio": _improvement_ratio(runtime_before_mean_ms, runtime_after_mean_ms),
        "memory_improvement_ratio": _improvement_ratio(memory_before_mean, memory_after_mean),
        "memory_area_improvement_ratio": _improvement_ratio(memory_area_before, memory_area_after),
        "compile_error": int(
            bool(before_result.get("compile_error")) or bool(after_result.get("compile_error"))
        ),
        "test_error": int(bool(before_result.get("test_error")) or bool(after_result.get("test_error"))),
        "timeout": int(bool(before_result.get("timeout")) or bool(after_result.get("timeout"))),
        "compile_error_before": int(bool(before_result.get("compile_error"))),
        "compile_error_after": int(bool(after_result.get("compile_error"))),
        "test_error_before": int(bool(before_result.get("test_error"))),
        "test_error_after": int(bool(after_result.get("test_error"))),
        "timeout_before": int(bool(before_result.get("timeout"))),
        "timeout_after": int(bool(after_result.get("timeout"))),
        "runtime_before_std_ms": before_result.get("runtime_std_ms"),
        "runtime_after_std_ms": after_result.get("runtime_std_ms"),
        "runtime_before_cv": before_result.get("runtime_cv"),
        "runtime_after_cv": after_result.get("runtime_cv"),
        "memory_before_std": before_result.get("memory_std"),
        "memory_after_std": after_result.get("memory_std"),
        "memory_before_cv": before_result.get("memory_cv"),
        "memory_after_cv": after_result.get("memory_cv"),
        "baseline_code_path": make_relative(Path(before_result["source_path"]), config.project_root),
        "raw_response_path": generation_record["raw_text_path"],
        "raw_response_json_path": generation_record["raw_json_path"],
        "cleaned_code_path": generation_record["cleaned_code_path"],
        "prompt_path": generation_record["prompt_path"],
        "signature_valid": int(bool(generation_record["signature_valid"])),
        "model_name": generation_record["model_name"],
        "from_cache": int(bool(generation_record["from_cache"])),
        "official_results_json_path": after_result.get("official_results_json_path", ""),
        "official_summary_json_path": after_result.get("official_summary_json_path", ""),
    }


def _find_effibench_root(dataset_path: Path) -> Path:
    candidates = [dataset_path] + list(dataset_path.parents)
    for candidate in candidates:
        root = candidate if candidate.is_dir() else candidate.parent
        if (root / "src" / "code_efficiency_calculator.py").exists():
            return root
    raise FileNotFoundError(
        f"Could not locate an EffiBench checkout by walking upward from dataset path {dataset_path}."
    )


def _official_input_path(
    config: ExperimentConfig,
    objective: str,
    prompt_detail: str,
    model_label: str,
) -> Path:
    return (
        config.resolve_path(config.paths.results_dir)
        / "official_inputs"
        / objective
        / prompt_detail
        / f"{model_label}.json"
    )


def _official_summary_path(
    config: ExperimentConfig,
    objective: str,
    prompt_detail: str,
    model_label: str,
) -> Path:
    return (
        config.resolve_path(config.paths.results_dir)
        / "official_summaries"
        / objective
        / prompt_detail
        / f"{model_label}.json"
    )


def _official_stdout_path(
    config: ExperimentConfig,
    objective: str,
    prompt_detail: str,
    model_label: str,
) -> Path:
    return (
        config.resolve_path(config.paths.results_dir)
        / "official_logs"
        / objective
        / prompt_detail
        / f"{model_label}.stdout.txt"
    )


def _official_stderr_path(
    config: ExperimentConfig,
    objective: str,
    prompt_detail: str,
    model_label: str,
) -> Path:
    return (
        config.resolve_path(config.paths.results_dir)
        / "official_logs"
        / objective
        / prompt_detail
        / f"{model_label}.stderr.txt"
    )


def _model_label(model_name: str, objective: str, prompt_detail: str) -> str:
    return sanitize_task_id(f"{model_name}_{objective}_{prompt_detail}")


def _sort_key(task_id: str) -> tuple[int, str]:
    if task_id.isdigit():
        return (0, f"{int(task_id):08d}")
    return (1, task_id)


def _normalize_difficulty(value: str) -> str:
    return value.strip().casefold()


def _improvement_ratio(before_value: float | None, after_value: float | None) -> float | None:
    if before_value is None or after_value in (None, 0):
        return None
    return before_value / after_value


def _ms_to_seconds(value: float | None) -> float | None:
    if value is None:
        return None
    return float(value) / 1000.0


def _build_run_manifest(config: ExperimentConfig, tasks: list[EffiBenchTask]) -> dict[str, object]:
    python_executable = config.resolve_executable(config.toolchain.python_executable)
    return {
        "benchmark": "effibench",
        "platform": platform.platform(),
        "python_version": sys.version,
        "dataset_path": config.dataset_path,
        "language": config.language,
        "objectives": config.objectives,
        "prompt_detail_levels": config.prompt_detail_levels,
        "selected_task_ids": [task.task_id for task in tasks],
        "selected_difficulty_levels": config.selected_difficulty_levels,
        "max_tasks": config.max_tasks,
        "model_name": config.model.name,
        "tool_versions": {
            "python": _command_version([python_executable, "--version"]),
            "mprof": _command_version([_resolve_mprof_executable(python_executable), "--help"]),
        },
    }


def _resolve_mprof_executable(python_executable: str) -> str:
    python_path = Path(python_executable).expanduser()
    if python_path.is_absolute() or python_path.parent != Path("."):
        candidate = python_path.parent / "mprof"
        if candidate.exists():
            return str(candidate)
    return "mprof"


def _command_version(command: list[str]) -> str:
    executable = shutil.which(command[0])
    if executable is None and Path(command[0]).exists():
        executable = command[0]
    if executable is None:
        return f"{command[0]} not found"
    try:
        completed = subprocess.run(
            [executable, *command[1:]],
            capture_output=True,
            text=True,
            timeout=10,
            check=False,
        )
    except Exception as exc:  # noqa: BLE001
        return f"error: {exc}"
    return (completed.stdout or completed.stderr).strip()
