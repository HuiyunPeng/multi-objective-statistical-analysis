from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

import yaml

from .utils import ensure_directory

SUPPORTED_OBJECTIVES = {"runtime", "memory", "balanced"}
SUPPORTED_PROMPT_DETAIL_LEVELS = {"minimal", "detailed"}


@dataclass
class ModelConfig:
    name: str = "gpt-5.4"
    reasoning_effort: str = "medium"
    temperature: float | None = None
    max_output_tokens: int = 16000
    retries: int = 3
    retry_backoff_seconds: float = 2.0
    cache_dir: str = "results/cache/model_outputs"
    base_url: str | None = None


@dataclass
class ToolchainConfig:
    python_executable: str = "python3"
    cpp_compiler: str = "g++"
    cpp_compile_flags: list[str] = field(default_factory=lambda: ["-std=c++17", "-O2"])
    cpp_link_flags: list[str] = field(default_factory=list)


@dataclass
class PathsConfig:
    results_dir: str = "results"
    analysis_dir: str = "results/analysis"
    prompts_dir: str = "prompts"
    generated_code_dir: str = "generated_code"
    logs_dir: str = "logs"
    raw_responses_dir: str = "results/raw_responses"
    generation_metadata_dir: str = "results/generation_metadata"
    evaluation_dir: str = "results/evaluations"
    baseline_code_dir: str = "generated_code/baseline"
    optimized_code_dir: str = "generated_code/optimized"
    selected_tasks_manifest: str = "results/selected_tasks.json"
    run_manifest: str = "results/run_manifest.json"
    raw_runs_csv: str = "results/raw_runs.csv"
    summary_csv: str = "results/analysis_ready.csv"


@dataclass
class ExperimentConfig:
    dataset_path: str = "benchmark/human_eval_cpp.json"
    language: str = "cpp"
    objectives: list[str] = field(default_factory=lambda: ["runtime", "memory", "balanced"])
    prompt_detail_levels: list[str] = field(default_factory=lambda: ["minimal", "detailed"])
    selected_task_ids: list[str] = field(default_factory=list)
    max_tasks: int | None = None
    warmup_runs: int = 1
    num_repetitions: int = 5
    compile_timeout: int = 20
    run_timeout: int = 20
    model: ModelConfig = field(default_factory=ModelConfig)
    paths: PathsConfig = field(default_factory=PathsConfig)
    toolchain: ToolchainConfig = field(default_factory=ToolchainConfig)
    overwrite_existing: bool = False
    project_root: Path = field(default_factory=lambda: Path.cwd())

    def resolve_path(self, path_value: str) -> Path:
        return (self.project_root / path_value).resolve()

    def ensure_directories(self) -> None:
        for path_value in (
            self.model.cache_dir,
            self.paths.results_dir,
            self.paths.analysis_dir,
            self.paths.prompts_dir,
            self.paths.generated_code_dir,
            self.paths.logs_dir,
            self.paths.raw_responses_dir,
            self.paths.generation_metadata_dir,
            self.paths.evaluation_dir,
            self.paths.baseline_code_dir,
            self.paths.optimized_code_dir,
        ):
            ensure_directory(self.resolve_path(path_value))

    def validate(self) -> None:
        if not self.objectives:
            raise ValueError("config.objectives must not be empty.")
        if not self.prompt_detail_levels:
            raise ValueError("config.prompt_detail_levels must not be empty.")

        invalid_objectives = sorted(set(self.objectives) - SUPPORTED_OBJECTIVES)
        if invalid_objectives:
            raise ValueError(f"Unsupported objectives: {invalid_objectives}")

        invalid_prompt_levels = sorted(
            set(self.prompt_detail_levels) - SUPPORTED_PROMPT_DETAIL_LEVELS
        )
        if invalid_prompt_levels:
            raise ValueError(f"Unsupported prompt detail levels: {invalid_prompt_levels}")

        if self.max_tasks is not None and self.max_tasks <= 0:
            raise ValueError("config.max_tasks must be at least 1 when provided.")
        if self.warmup_runs < 0:
            raise ValueError("config.warmup_runs must be at least 0.")
        if self.num_repetitions <= 0:
            raise ValueError("config.num_repetitions must be at least 1.")
        if self.compile_timeout <= 0:
            raise ValueError("config.compile_timeout must be at least 1.")
        if self.run_timeout <= 0:
            raise ValueError("config.run_timeout must be at least 1.")


def _build_dataclass(model_cls: type[Any], payload: dict[str, Any] | None) -> Any:
    payload = payload or {}
    return model_cls(**payload)


def load_config(path: str | Path) -> ExperimentConfig:
    config_path = Path(path).resolve()
    raw_payload = yaml.safe_load(config_path.read_text(encoding="utf-8")) or {}
    config = ExperimentConfig(
        dataset_path=str(raw_payload.get("dataset_path", "benchmark/human_eval_cpp.json")),
        language=str(raw_payload.get("language", "cpp")),
        objectives=[str(value) for value in raw_payload.get("objectives", ["runtime", "memory", "balanced"])],
        prompt_detail_levels=[
            str(value) for value in raw_payload.get("prompt_detail_levels", ["minimal", "detailed"])
        ],
        selected_task_ids=[str(value) for value in raw_payload.get("selected_task_ids", [])],
        max_tasks=(
            int(raw_payload["max_tasks"])
            if raw_payload.get("max_tasks") is not None
            else None
        ),
        warmup_runs=int(raw_payload.get("warmup_runs", 1)),
        num_repetitions=int(raw_payload.get("num_repetitions", 5)),
        compile_timeout=int(raw_payload.get("compile_timeout", 20)),
        run_timeout=int(raw_payload.get("run_timeout", 20)),
        model=_build_dataclass(ModelConfig, raw_payload.get("model")),
        paths=_build_dataclass(PathsConfig, raw_payload.get("paths")),
        toolchain=_build_dataclass(ToolchainConfig, raw_payload.get("toolchain")),
        overwrite_existing=bool(raw_payload.get("overwrite_existing", False)),
        project_root=config_path.parent,
    )
    config.validate()
    config.ensure_directories()
    return config
