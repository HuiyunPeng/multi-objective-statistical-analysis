from __future__ import annotations

from pathlib import Path

from .config import ExperimentConfig
from .utils import sanitize_task_id

LANGUAGE_EXTENSIONS = {
    "python": ".py",
    "cpp": ".cpp",
    "java": ".java",
}


def extension_for_language(language: str) -> str:
    return LANGUAGE_EXTENSIONS[language]


def _task_name(task_id: str) -> str:
    return sanitize_task_id(task_id)


def prompt_path(
    config: ExperimentConfig,
    task_id: str,
    language: str,
    objective: str,
    prompt_detail: str,
) -> Path:
    return config.resolve_path(config.paths.prompts_dir) / objective / prompt_detail / language / (
        f"{_task_name(task_id)}.txt"
    )


def raw_text_response_path(
    config: ExperimentConfig,
    task_id: str,
    language: str,
    objective: str,
    prompt_detail: str,
) -> Path:
    return (
        config.resolve_path(config.paths.raw_responses_dir)
        / objective
        / prompt_detail
        / language
        / f"{_task_name(task_id)}.txt"
    )


def raw_json_response_path(
    config: ExperimentConfig,
    task_id: str,
    language: str,
    objective: str,
    prompt_detail: str,
) -> Path:
    return (
        config.resolve_path(config.paths.raw_responses_dir)
        / objective
        / prompt_detail
        / language
        / f"{_task_name(task_id)}.json"
    )


def cleaned_code_path(
    config: ExperimentConfig,
    task_id: str,
    language: str,
    objective: str,
    prompt_detail: str,
) -> Path:
    extension = extension_for_language(language)
    return (
        config.resolve_path(config.paths.optimized_code_dir)
        / objective
        / prompt_detail
        / language
        / f"{_task_name(task_id)}{extension}"
    )


def baseline_code_path(config: ExperimentConfig, task_id: str, language: str) -> Path:
    extension = extension_for_language(language)
    return config.resolve_path(config.paths.baseline_code_dir) / language / (
        f"{_task_name(task_id)}{extension}"
    )


def generation_metadata_path(
    config: ExperimentConfig,
    task_id: str,
    language: str,
    objective: str,
    prompt_detail: str,
) -> Path:
    return (
        config.resolve_path(config.paths.generation_metadata_dir)
        / objective
        / prompt_detail
        / language
        / f"{_task_name(task_id)}.json"
    )


def evaluation_path(
    config: ExperimentConfig,
    variant: str,
    task_id: str,
    language: str,
    objective: str | None = None,
    prompt_detail: str | None = None,
) -> Path:
    base_path = config.resolve_path(config.paths.evaluation_dir) / variant
    if objective is not None:
        base_path = base_path / objective
    if prompt_detail is not None:
        base_path = base_path / prompt_detail
    base_path = base_path / language
    return base_path / f"{_task_name(task_id)}.json"
