from __future__ import annotations

from pathlib import Path
from typing import Any, Iterable

from .artifact_paths import evaluation_path, generation_metadata_path
from .config import ExperimentConfig
from .models import ObjectiveMode, TaskRecord
from .utils import make_relative, read_json, write_csv

OBJECTIVES: tuple[ObjectiveMode, ...] = ("runtime", "memory", "balanced")


def write_aggregated_results(
    config: ExperimentConfig,
    aligned_tasks: dict[str, dict[str, TaskRecord]],
) -> tuple[Path, Path]:
    root = config.project_root
    raw_rows: list[dict[str, Any]] = []
    summary_rows: list[dict[str, Any]] = []

    for language, task_map in aligned_tasks.items():
        for problem_id, task in task_map.items():
            before_result = read_json(evaluation_path(config, "baseline", problem_id, language))
            raw_rows.extend(_measurement_rows(before_result, root))

            for objective in OBJECTIVES:
                after_result = read_json(
                    evaluation_path(config, "optimized", problem_id, language, objective)
                )
                generation_record = read_json(
                    generation_metadata_path(config, problem_id, language, objective)
                )
                raw_rows.extend(_measurement_rows(after_result, root))
                summary_rows.append(
                    _summary_row(
                        config=config,
                        task=task,
                        objective=objective,
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


def _measurement_rows(result: dict[str, Any], root: Path) -> Iterable[dict[str, Any]]:
    for sample in result.get("samples", []):
        yield {
            "problem_id": result["problem_id"],
            "task_id": result["task_id"],
            "language": result["language"],
            "objective": result.get("objective") or "",
            "variant": result["variant"],
            "repetition_index": sample["repetition_index"],
            "runtime_seconds": sample["runtime_seconds"],
            "peak_memory_bytes": sample["peak_memory_bytes"],
            "returncode": sample["returncode"],
            "stdout": sample["stdout"],
            "stderr": sample["stderr"],
            "correctness_pass": int(bool(result["correctness_pass"])),
            "compile_error": int(bool(result["compile_error"])),
            "test_error": int(bool(result["test_error"])),
            "timeout": int(bool(result["timeout"])),
            "source_path": make_relative(Path(result["source_path"]), root),
        }


def _summary_row(
    config: ExperimentConfig,
    task: TaskRecord,
    objective: str,
    before_result: dict[str, Any],
    after_result: dict[str, Any],
    generation_record: dict[str, Any],
) -> dict[str, Any]:
    runtime_before_mean = before_result.get("runtime_mean")
    runtime_after_mean = after_result.get("runtime_mean")
    memory_before_mean = before_result.get("memory_mean")
    memory_after_mean = after_result.get("memory_mean")

    return {
        "problem_id": task.problem_id,
        "task_id": task.task_id,
        "language": task.language,
        "objective": objective,
        "correctness_before": int(bool(before_result.get("correctness_pass"))),
        "correctness_after": int(bool(after_result.get("correctness_pass"))),
        "runtime_before_mean": runtime_before_mean,
        "runtime_after_mean": runtime_after_mean,
        "memory_before_mean": memory_before_mean,
        "memory_after_mean": memory_after_mean,
        "runtime_improvement_ratio": _improvement_ratio(runtime_before_mean, runtime_after_mean),
        "memory_improvement_ratio": _improvement_ratio(memory_before_mean, memory_after_mean),
        "compile_error": int(
            bool(before_result.get("compile_error")) or bool(after_result.get("compile_error"))
        ),
        "test_error": int(
            bool(before_result.get("test_error")) or bool(after_result.get("test_error"))
        ),
        "timeout": int(bool(before_result.get("timeout")) or bool(after_result.get("timeout"))),
        "compile_error_before": int(bool(before_result.get("compile_error"))),
        "compile_error_after": int(bool(after_result.get("compile_error"))),
        "test_error_before": int(bool(before_result.get("test_error"))),
        "test_error_after": int(bool(after_result.get("test_error"))),
        "timeout_before": int(bool(before_result.get("timeout"))),
        "timeout_after": int(bool(after_result.get("timeout"))),
        "runtime_before_std": before_result.get("runtime_std"),
        "runtime_after_std": after_result.get("runtime_std"),
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
    }


def _improvement_ratio(before_value: float | None, after_value: float | None) -> float | None:
    if before_value is None or after_value in (None, 0):
        return None
    return before_value / after_value


RAW_FIELDNAMES = [
    "problem_id",
    "task_id",
    "language",
    "objective",
    "variant",
    "repetition_index",
    "runtime_seconds",
    "peak_memory_bytes",
    "returncode",
    "stdout",
    "stderr",
    "correctness_pass",
    "compile_error",
    "test_error",
    "timeout",
    "source_path",
]

SUMMARY_FIELDNAMES = [
    "problem_id",
    "task_id",
    "language",
    "objective",
    "correctness_before",
    "correctness_after",
    "runtime_before_mean",
    "runtime_after_mean",
    "memory_before_mean",
    "memory_after_mean",
    "runtime_improvement_ratio",
    "memory_improvement_ratio",
    "compile_error",
    "test_error",
    "timeout",
    "compile_error_before",
    "compile_error_after",
    "test_error_before",
    "test_error_after",
    "timeout_before",
    "timeout_after",
    "runtime_before_std",
    "runtime_after_std",
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
]
