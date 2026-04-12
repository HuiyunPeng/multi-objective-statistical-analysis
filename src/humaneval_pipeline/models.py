from __future__ import annotations

from dataclasses import asdict, dataclass, field
from typing import Any, Literal

Language = Literal["python", "cpp", "java"]
ObjectiveMode = Literal["runtime", "memory", "balanced"]


@dataclass(frozen=True)
class TaskRecord:
    problem_id: str
    task_id: str
    language: Language
    prompt: str
    declaration: str
    canonical_solution: str
    test: str
    example_test: str

    @property
    def baseline_source(self) -> str:
        return f"{self.prompt}{self.canonical_solution}"

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)


@dataclass(frozen=True)
class GenerationRecord:
    problem_id: str
    task_id: str
    language: Language
    objective: ObjectiveMode
    prompt_path: str
    raw_text_path: str
    raw_json_path: str
    cleaned_code_path: str
    cache_key: str
    signature_valid: bool
    cleaner_notes: list[str]
    model_name: str
    from_cache: bool

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)


@dataclass(frozen=True)
class BenchmarkSample:
    repetition_index: int
    runtime_seconds: float
    peak_memory_bytes: int
    returncode: int
    stdout: str
    stderr: str

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)


@dataclass
class BenchmarkResult:
    problem_id: str
    task_id: str
    language: Language
    variant: str
    objective: str | None
    source_path: str
    correctness_pass: bool
    compile_error: bool
    test_error: bool
    timeout: bool
    compile_stdout: str = ""
    compile_stderr: str = ""
    compile_returncode: int | None = None
    correctness_stdout: str = ""
    correctness_stderr: str = ""
    correctness_returncode: int | None = None
    runtime_mean: float | None = None
    runtime_std: float | None = None
    runtime_cv: float | None = None
    memory_mean: float | None = None
    memory_std: float | None = None
    memory_cv: float | None = None
    samples: list[BenchmarkSample] = field(default_factory=list)

    def to_dict(self) -> dict[str, Any]:
        payload = asdict(self)
        payload["samples"] = [sample.to_dict() for sample in self.samples]
        return payload


@dataclass(frozen=True)
class CleanedCodeResult:
    cleaned_code: str
    signature_valid: bool
    notes: list[str]


@dataclass(frozen=True)
class ModelCallResult:
    cache_key: str
    raw_text: str
    response_json: dict[str, Any]
    from_cache: bool
