from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

import yaml

from .utils import ensure_directory


@dataclass
class DatasetConfig:
    source_urls: list[str]
    local_files: dict[str, str] = field(default_factory=dict)
    languages: list[str] = field(default_factory=lambda: ["python", "cpp", "java"])
    selected_problem_ids: list[str] = field(default_factory=list)
    pilot_size: int = 10
    cache_dir: str = "results/cache/datasets"


@dataclass
class ModelConfig:
    name: str = "gpt-5.4"
    reasoning_effort: str = "medium"
    temperature: float = 0.0
    max_output_tokens: int = 16000
    retries: int = 3
    retry_backoff_seconds: float = 2.0
    cache_dir: str = "results/cache/model_outputs"
    base_url: str | None = None


@dataclass
class BenchmarkConfig:
    warmup_runs: int = 1
    measured_runs: int = 5
    poll_interval_seconds: float = 0.01


@dataclass
class ExecutionConfig:
    compile_timeout_seconds: int = 30
    timeouts: dict[str, int] = field(
        default_factory=lambda: {"python": 20, "cpp": 20, "java": 20}
    )
    python_executable: str = "python3"
    cpp_compiler: str = "g++"
    cpp_compile_flags: list[str] = field(default_factory=lambda: ["-std=c++17", "-O2"])
    cpp_link_flags: list[str] = field(default_factory=list)
    java_compiler: str = "javac"
    java_runtime: str = "java"
    java_compile_flags: list[str] = field(default_factory=list)
    java_runtime_flags: list[str] = field(default_factory=lambda: ["-ea"])

    def timeout_for(self, language: str) -> int:
        return int(self.timeouts[language])


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
    dataset: DatasetConfig
    model: ModelConfig = field(default_factory=ModelConfig)
    benchmark: BenchmarkConfig = field(default_factory=BenchmarkConfig)
    execution: ExecutionConfig = field(default_factory=ExecutionConfig)
    paths: PathsConfig = field(default_factory=PathsConfig)
    overwrite_existing: bool = False
    project_root: Path = field(default_factory=lambda: Path.cwd())

    def resolve_path(self, path_value: str) -> Path:
        return (self.project_root / path_value).resolve()

    def ensure_directories(self) -> None:
        for path_value in (
            self.dataset.cache_dir,
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


def _build_dataclass(model_cls: type[Any], payload: dict[str, Any] | None) -> Any:
    payload = payload or {}
    return model_cls(**payload)


def load_config(path: str | Path) -> ExperimentConfig:
    config_path = Path(path).resolve()
    raw_payload = yaml.safe_load(config_path.read_text(encoding="utf-8")) or {}
    config = ExperimentConfig(
        dataset=_build_dataclass(DatasetConfig, raw_payload.get("dataset")),
        model=_build_dataclass(ModelConfig, raw_payload.get("model")),
        benchmark=_build_dataclass(BenchmarkConfig, raw_payload.get("benchmark")),
        execution=_build_dataclass(ExecutionConfig, raw_payload.get("execution")),
        paths=_build_dataclass(PathsConfig, raw_payload.get("paths")),
        overwrite_existing=bool(raw_payload.get("overwrite_existing", False)),
        project_root=config_path.parent,
    )
    config.ensure_directories()
    return config
