from __future__ import annotations

import platform
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Iterable

from .aggregator import OBJECTIVES, write_aggregated_results
from .artifact_paths import (
    baseline_code_path,
    cleaned_code_path,
    evaluation_path,
    generation_metadata_path,
    prompt_path,
    raw_json_response_path,
    raw_text_response_path,
)
from .benchmark import evaluate_solution
from .config import ExperimentConfig, load_config
from .dataset_loader import HumanEvalXLoader
from .logging_utils import configure_logging
from .model_client import OpenAIModelClient
from .models import BenchmarkResult, TaskRecord
from .prompts import build_prompt
from .response_cleaner import clean_model_response
from .utils import make_relative, read_json, write_json, write_text

STAGE_NAMES = ("prepare", "generate", "evaluate", "aggregate")


def run_pipeline(config_path: str | Path, stages: Iterable[str] | None = None) -> None:
    config = load_config(config_path)
    logger = configure_logging(config.resolve_path(config.paths.logs_dir) / "pipeline.log")
    selected_stages = tuple(stages or STAGE_NAMES)
    invalid = set(selected_stages) - set(STAGE_NAMES)
    if invalid:
        raise ValueError(f"Unsupported pipeline stages: {sorted(invalid)}")

    logger.info("Running pipeline stages: %s", ", ".join(selected_stages))
    aligned_tasks: dict[str, dict[str, TaskRecord]] | None = None

    if "prepare" in selected_stages:
        aligned_tasks = _prepare(config, logger)
    else:
        aligned_tasks = _load_selected_manifest(config)

    if "generate" in selected_stages:
        _generate(config, aligned_tasks, logger)

    if "evaluate" in selected_stages:
        _evaluate(config, aligned_tasks, logger)

    if "aggregate" in selected_stages:
        raw_path, summary_path = write_aggregated_results(config, aligned_tasks)
        logger.info("Wrote raw runs CSV to %s", raw_path)
        logger.info("Wrote summary CSV to %s", summary_path)


def _prepare(config: ExperimentConfig, logger) -> dict[str, dict[str, TaskRecord]]:
    loader = HumanEvalXLoader(config, logger)
    aligned_tasks = loader.load_aligned_tasks()
    loader.save_selected_manifest(aligned_tasks)

    for language, task_map in aligned_tasks.items():
        for task in task_map.values():
            write_text(baseline_code_path(config, task.problem_id, language), task.baseline_source)

    write_json(config.resolve_path(config.paths.run_manifest), _build_run_manifest(config, aligned_tasks))
    logger.info(
        "Prepared %s shared problem IDs across languages %s",
        len(next(iter(aligned_tasks.values()))),
        ", ".join(config.dataset.languages),
    )
    return aligned_tasks


def _generate(config: ExperimentConfig, aligned_tasks: dict[str, dict[str, TaskRecord]], logger) -> None:
    client = OpenAIModelClient(config)
    for language, task_map in aligned_tasks.items():
        for task in task_map.values():
            for objective in OBJECTIVES:
                prompt = build_prompt(task.language, objective, task.baseline_source)
                prompt_file = prompt_path(config, task.problem_id, language, objective)
                raw_text_path = raw_text_response_path(config, task.problem_id, language, objective)
                raw_json_path = raw_json_response_path(config, task.problem_id, language, objective)
                cleaned_path = cleaned_code_path(config, task.problem_id, language, objective)
                metadata_path = generation_metadata_path(config, task.problem_id, language, objective)

                write_text(prompt_file, prompt)
                model_result = client.generate(prompt)
                write_text(raw_text_path, model_result.raw_text)
                write_json(raw_json_path, model_result.response_json)

                cleaned = clean_model_response(model_result.raw_text, task.declaration, task.language)
                write_text(cleaned_path, cleaned.cleaned_code)
                write_json(
                    metadata_path,
                    {
                        "problem_id": task.problem_id,
                        "task_id": task.task_id,
                        "language": language,
                        "objective": objective,
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
                    "Generated %s | %s | %s | cache=%s",
                    task.problem_id,
                    language,
                    objective,
                    model_result.from_cache,
                )


def _evaluate(config: ExperimentConfig, aligned_tasks: dict[str, dict[str, TaskRecord]], logger) -> None:
    for language, task_map in aligned_tasks.items():
        for task in task_map.values():
            baseline_source_file = baseline_code_path(config, task.problem_id, language)
            baseline_eval_path = evaluation_path(config, "baseline", task.problem_id, language)
            if (
                config.overwrite_existing
                or not baseline_eval_path.exists()
                or _should_rerun_legacy_java_compile_case(baseline_eval_path, language)
            ):
                baseline_result = evaluate_solution(
                    task=task,
                    code=baseline_source_file.read_text(encoding="utf-8"),
                    source_path=baseline_source_file,
                    variant="before",
                    objective=None,
                    execution=config.execution,
                    benchmark=config.benchmark,
                )
                write_json(baseline_eval_path, baseline_result.to_dict())
                logger.info("Evaluated baseline | %s | %s", task.problem_id, language)

            for objective in OBJECTIVES:
                metadata = read_json(generation_metadata_path(config, task.problem_id, language, objective))
                optimized_source_file = cleaned_code_path(config, task.problem_id, language, objective)
                optimized_eval_path = evaluation_path(
                    config, "optimized", task.problem_id, language, objective
                )
                if (
                    not config.overwrite_existing
                    and optimized_eval_path.exists()
                    and not _should_rerun_signature_skipped_case(optimized_eval_path, metadata)
                    and not _should_rerun_legacy_java_compile_case(optimized_eval_path, language)
                ):
                    continue

                if not metadata.get("signature_valid"):
                    invalid_result = BenchmarkResult(
                        problem_id=task.problem_id,
                        task_id=task.task_id,
                        language=task.language,
                        variant="after",
                        objective=objective,
                        source_path=str(optimized_source_file),
                        correctness_pass=False,
                        compile_error=False,
                        test_error=True,
                        timeout=False,
                        correctness_stderr="Signature validation failed before execution.",
                    )
                    write_json(optimized_eval_path, invalid_result.to_dict())
                    logger.info(
                        "Skipped execution after failed signature validation | %s | %s | %s",
                        task.problem_id,
                        language,
                        objective,
                    )
                    continue

                optimized_result = evaluate_solution(
                    task=task,
                    code=optimized_source_file.read_text(encoding="utf-8"),
                    source_path=optimized_source_file,
                    variant="after",
                    objective=objective,
                    execution=config.execution,
                    benchmark=config.benchmark,
                )
                write_json(optimized_eval_path, optimized_result.to_dict())
                logger.info("Evaluated optimized | %s | %s | %s", task.problem_id, language, objective)


def _should_rerun_signature_skipped_case(optimized_eval_path: Path, metadata: dict[str, object]) -> bool:
    if not optimized_eval_path.exists():
        return False

    prior_result = read_json(optimized_eval_path)
    prior_signature_skip = (
        prior_result.get("correctness_stderr") == "Signature validation failed before execution."
    )
    current_signature_valid = bool(metadata.get("signature_valid"))
    return prior_signature_skip and current_signature_valid


def _should_rerun_legacy_java_compile_case(result_path: Path, language: str) -> bool:
    if language != "java" or not result_path.exists():
        return False
    prior_result = read_json(result_path)
    compile_stderr = str(prior_result.get("compile_stderr", ""))
    return "class Main is public, should be declared in a file named Main.java" in compile_stderr


def _load_selected_manifest(config: ExperimentConfig) -> dict[str, dict[str, TaskRecord]]:
    manifest_path = config.resolve_path(config.paths.selected_tasks_manifest)
    if not manifest_path.exists():
        raise FileNotFoundError(
            "Selected task manifest not found. Run the prepare stage first or include it in --stages."
        )

    payload = read_json(manifest_path)
    aligned_tasks: dict[str, dict[str, TaskRecord]] = {}
    for language, tasks in payload["tasks"].items():
        aligned_tasks[language] = {
            task_payload["problem_id"]: TaskRecord(**task_payload) for task_payload in tasks
        }
    return aligned_tasks


def _build_run_manifest(
    config: ExperimentConfig, aligned_tasks: dict[str, dict[str, TaskRecord]]
) -> dict[str, object]:
    return {
        "platform": platform.platform(),
        "python_version": sys.version,
        "selected_problem_ids": list(next(iter(aligned_tasks.values())).keys()),
        "dataset_languages": config.dataset.languages,
        "dataset_source_urls": config.dataset.source_urls,
        "tool_versions": {
            "python": _command_version([config.execution.python_executable, "--version"]),
            "cpp_compiler": _command_version([config.execution.cpp_compiler, "--version"]),
            "javac": _command_version([config.execution.java_compiler, "-version"]),
            "java": _command_version([config.execution.java_runtime, "-version"]),
        },
    }


def _command_version(command: list[str]) -> str:
    executable = shutil.which(command[0])
    if executable is None:
        return f"{command[0]} not found"
    try:
        completed = subprocess.run(
            command,
            capture_output=True,
            text=True,
            timeout=10,
            check=False,
        )
    except Exception as exc:  # noqa: BLE001
        return f"error: {exc}"
    return (completed.stdout or completed.stderr).strip()
