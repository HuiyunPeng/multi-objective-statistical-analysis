from __future__ import annotations

import platform
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Iterable

from .aggregator import write_aggregated_results
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
from .dataset_loader import BenchmarkDatasetLoader
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
    tasks: list[TaskRecord] | None = None

    if "prepare" in selected_stages:
        tasks = _prepare(config, logger)
    else:
        tasks = _load_selected_manifest(config)

    if "generate" in selected_stages:
        _generate(config, tasks, logger)

    if "evaluate" in selected_stages:
        _evaluate(config, tasks, logger)

    if "aggregate" in selected_stages:
        raw_path, summary_path = write_aggregated_results(config, tasks)
        logger.info("Wrote raw runs CSV to %s", raw_path)
        logger.info("Wrote summary CSV to %s", summary_path)


def _prepare(config: ExperimentConfig, logger) -> list[TaskRecord]:
    loader = BenchmarkDatasetLoader(config, logger)
    tasks = loader.load_tasks()
    loader.save_selected_manifest(tasks)

    for task in tasks:
        write_text(baseline_code_path(config, task.task_id, task.language), task.baseline_source)

    write_json(config.resolve_path(config.paths.run_manifest), _build_run_manifest(config, tasks))
    logger.info(
        "Prepared %s tasks for language %s from %s",
        len(tasks),
        config.language,
        config.dataset_path,
    )
    return tasks


def _generate(config: ExperimentConfig, tasks: list[TaskRecord], logger) -> None:
    client = OpenAIModelClient(config)
    for task in tasks:
        for objective in config.objectives:
            for prompt_detail in config.prompt_detail_levels:
                prompt = build_prompt(task.language, objective, prompt_detail, task.baseline_source)
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
                    task.function_code,
                    task.entry_point,
                    task.language,
                )
                write_text(cleaned_path, cleaned.cleaned_code)
                write_json(
                    metadata_path,
                    {
                        "task_id": task.task_id,
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
                    "Generated %s | %s | %s | cache=%s",
                    task.task_id,
                    objective,
                    prompt_detail,
                    model_result.from_cache,
                )


def _evaluate(config: ExperimentConfig, tasks: list[TaskRecord], logger) -> None:
    for task in tasks:
        baseline_source_file = baseline_code_path(config, task.task_id, task.language)
        baseline_eval_path = evaluation_path(config, "baseline", task.task_id, task.language)
        if config.overwrite_existing or not baseline_eval_path.exists():
            baseline_result = evaluate_solution(
                task=task,
                code=baseline_source_file.read_text(encoding="utf-8"),
                source_path=baseline_source_file,
                variant="before",
                objective=None,
                prompt_detail=None,
                config=config,
            )
            write_json(baseline_eval_path, baseline_result.to_dict())
            logger.info("Evaluated baseline | %s | %s", task.task_id, task.language)

        for objective in config.objectives:
            for prompt_detail in config.prompt_detail_levels:
                metadata = read_json(
                    generation_metadata_path(
                        config, task.task_id, task.language, objective, prompt_detail
                    )
                )
                optimized_source_file = cleaned_code_path(
                    config, task.task_id, task.language, objective, prompt_detail
                )
                optimized_eval_path = evaluation_path(
                    config,
                    "optimized",
                    task.task_id,
                    task.language,
                    objective,
                    prompt_detail,
                )
                if (
                    not config.overwrite_existing
                    and optimized_eval_path.exists()
                    and not _should_rerun_signature_skipped_case(optimized_eval_path, metadata)
                ):
                    continue

                if not metadata.get("signature_valid"):
                    invalid_result = BenchmarkResult(
                        task_id=task.task_id,
                        language=task.language,
                        variant="after",
                        objective=objective,
                        prompt_detail=prompt_detail,
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
                        task.task_id,
                        objective,
                        prompt_detail,
                    )
                    continue

                optimized_result = evaluate_solution(
                    task=task,
                    code=optimized_source_file.read_text(encoding="utf-8"),
                    source_path=optimized_source_file,
                    variant="after",
                    objective=objective,
                    prompt_detail=prompt_detail,
                    config=config,
                )
                write_json(optimized_eval_path, optimized_result.to_dict())
                logger.info(
                    "Evaluated optimized | %s | %s | %s",
                    task.task_id,
                    objective,
                    prompt_detail,
                )


def _should_rerun_signature_skipped_case(optimized_eval_path: Path, metadata: dict[str, object]) -> bool:
    if not optimized_eval_path.exists():
        return False

    prior_result = read_json(optimized_eval_path)
    prior_signature_skip = (
        prior_result.get("correctness_stderr") == "Signature validation failed before execution."
    )
    current_signature_valid = bool(metadata.get("signature_valid"))
    return prior_signature_skip and current_signature_valid


def _load_selected_manifest(config: ExperimentConfig) -> list[TaskRecord]:
    manifest_path = config.resolve_path(config.paths.selected_tasks_manifest)
    if not manifest_path.exists():
        raise FileNotFoundError(
            "Selected task manifest not found. Run the prepare stage first or include it in --stages."
        )

    payload = read_json(manifest_path)
    return [TaskRecord(**task_payload) for task_payload in payload["tasks"]]


def _build_run_manifest(config: ExperimentConfig, tasks: list[TaskRecord]) -> dict[str, object]:
    python_executable = config.resolve_executable(config.toolchain.python_executable)
    tool_versions = {
        "python": _command_version([python_executable, "--version"]),
    }
    if config.language == "cpp":
        tool_versions["cpp_compiler"] = _command_version([config.toolchain.cpp_compiler, "--version"])

    return {
        "platform": platform.platform(),
        "python_version": sys.version,
        "dataset_path": config.dataset_path,
        "language": config.language,
        "objectives": config.objectives,
        "prompt_detail_levels": config.prompt_detail_levels,
        "selected_task_ids": [task.task_id for task in tasks],
        "max_tasks": config.max_tasks,
        "warmup_runs": config.warmup_runs,
        "num_repetitions": config.num_repetitions,
        "compile_timeout": config.compile_timeout,
        "run_timeout": config.run_timeout,
        "tool_versions": tool_versions,
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
