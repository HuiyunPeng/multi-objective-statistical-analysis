from __future__ import annotations

from pathlib import Path

from .config import ExperimentConfig
from .utils import sanitize_problem_id

LANGUAGE_EXTENSIONS = {
    "python": ".py",
    "cpp": ".cpp",
    "java": ".java",
}


def extension_for_language(language: str) -> str:
    return LANGUAGE_EXTENSIONS[language]


def _problem_name(problem_id: str) -> str:
    return sanitize_problem_id(problem_id)


def prompt_path(
    config: ExperimentConfig, problem_id: str, language: str, objective: str
) -> Path:
    return config.resolve_path(config.paths.prompts_dir) / objective / language / (
        f"{_problem_name(problem_id)}.txt"
    )


def raw_text_response_path(
    config: ExperimentConfig, problem_id: str, language: str, objective: str
) -> Path:
    return config.resolve_path(config.paths.raw_responses_dir) / objective / language / (
        f"{_problem_name(problem_id)}.txt"
    )


def raw_json_response_path(
    config: ExperimentConfig, problem_id: str, language: str, objective: str
) -> Path:
    return config.resolve_path(config.paths.raw_responses_dir) / objective / language / (
        f"{_problem_name(problem_id)}.json"
    )


def cleaned_code_path(
    config: ExperimentConfig, problem_id: str, language: str, objective: str
) -> Path:
    extension = extension_for_language(language)
    return config.resolve_path(config.paths.optimized_code_dir) / objective / language / (
        f"{_problem_name(problem_id)}{extension}"
    )


def baseline_code_path(config: ExperimentConfig, problem_id: str, language: str) -> Path:
    extension = extension_for_language(language)
    return config.resolve_path(config.paths.baseline_code_dir) / language / (
        f"{_problem_name(problem_id)}{extension}"
    )


def generation_metadata_path(
    config: ExperimentConfig, problem_id: str, language: str, objective: str
) -> Path:
    return config.resolve_path(config.paths.generation_metadata_dir) / objective / language / (
        f"{_problem_name(problem_id)}.json"
    )


def evaluation_path(
    config: ExperimentConfig,
    variant: str,
    problem_id: str,
    language: str,
    objective: str | None = None,
) -> Path:
    parts = [config.resolve_path(config.paths.evaluation_dir), variant]
    if objective is not None:
        parts.append(Path(objective))
    parts.append(Path(language))
    base_path = parts[0]
    for part in parts[1:]:
        base_path = base_path / part
    return base_path / f"{_problem_name(problem_id)}.json"
