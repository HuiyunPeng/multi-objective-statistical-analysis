from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any

REQUIRED_EFFIBENCH_RESULT_FIELDS = {
    "problem_idx",
    "task_name",
    "completion",
    "canonical_solution",
    "small_test_cases",
    "test_case",
}


@dataclass(frozen=True)
class EffiBenchDatMetrics:
    runtime_seconds: float
    max_memory_mb: float
    memory_usage_mb_seconds: float

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)


@dataclass(frozen=True)
class EffiBenchOfficialSummary:
    model_name: str
    num_tasks_requested: int
    num_tasks_measured: int
    average_execution_time_seconds: float | None
    normalized_execution_time: float | None
    average_max_memory_mb: float | None
    normalized_max_memory_usage: float | None
    average_memory_usage_mb_seconds: float | None
    normalized_memory_usage: float | None

    def to_dict(self) -> dict[str, Any]:
        return asdict(self)


def load_effibench_results(path: str | Path) -> list[dict[str, Any]]:
    result_path = Path(path).resolve()
    payload = json.loads(result_path.read_text(encoding="utf-8"))
    if not isinstance(payload, list):
        raise ValueError("EffiBench results JSON must contain a top-level array.")

    rows: list[dict[str, Any]] = []
    for index, row in enumerate(payload):
        if not isinstance(row, dict):
            raise ValueError(
                f"EffiBench results row {index} must be an object, got {type(row).__name__}."
            )
        missing = sorted(REQUIRED_EFFIBENCH_RESULT_FIELDS - row.keys())
        if missing:
            raise KeyError(
                f"EffiBench results row {index} is missing fields {missing}. "
                f"Available fields: {sorted(row.keys())}"
            )
        rows.append(row)
    return rows


def stage_effibench_results(
    input_json: str | Path,
    effibench_root: str | Path,
    model_name: str,
    limit: int | None = None,
) -> tuple[Path, int]:
    rows = load_effibench_results(input_json)
    if limit is not None:
        if limit <= 0:
            raise ValueError("--limit must be at least 1 when provided.")
        rows = rows[:limit]

    root = _resolve_effibench_root(effibench_root)
    staged_path = root / "results" / f"{model_name}.json"
    staged_path.parent.mkdir(parents=True, exist_ok=True)
    staged_path.write_text(json.dumps(rows, indent=2), encoding="utf-8")
    return staged_path, len(rows)


def run_official_effibench_evaluator(
    effibench_root: str | Path,
    model_name: str,
    python_executable: str | Path | None = None,
) -> subprocess.CompletedProcess[str]:
    root = _resolve_effibench_root(effibench_root)
    python_path = Path(python_executable or sys.executable).expanduser()
    if not python_path.is_absolute() and (
        python_path.parent != Path(".") or python_path.exists()
    ):
        python_path = Path(os.path.abspath(os.fspath(Path.cwd() / python_path)))

    env = os.environ.copy()
    search_path = env.get("PATH", "")
    if python_path.parent != Path("."):
        search_path = str(python_path.parent) + os.pathsep + search_path

    mprof_path = shutil.which("mprof", path=search_path)
    if mprof_path is None:
        raise FileNotFoundError(
            "mprof was not found next to the selected Python interpreter. "
            "Install memory_profiler in that environment first."
        )

    env["PATH"] = search_path
    command = [str(python_path), "code_efficiency_calculator.py", "--model", model_name]
    completed = subprocess.run(
        command,
        cwd=root / "src",
        env=env,
        capture_output=True,
        text=True,
        check=False,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            "EffiBench official evaluator failed.\n"
            f"stdout:\n{completed.stdout}\n"
            f"stderr:\n{completed.stderr}"
        )
    return completed


def summarize_official_effibench_results(
    effibench_root: str | Path,
    model_name: str,
    num_tasks_requested: int,
) -> EffiBenchOfficialSummary:
    root = _resolve_effibench_root(effibench_root)
    canonical_dir = root / "dat_results" / "canonical_solution"
    model_dir = root / "dat_results" / model_name

    canonical_memory_usage: dict[int, float] = {}
    canonical_execution_time: dict[int, float] = {}
    canonical_max_memory: dict[int, float] = {}
    for dat_file in canonical_dir.glob("*.dat"):
        problem_idx = int(dat_file.stem)
        canonical_memory_usage[problem_idx] = _calculate_memory_usage(dat_file)
        canonical_execution_time[problem_idx] = _calculate_runtime(dat_file)
        canonical_max_memory[problem_idx] = _report_max_memory_usage(dat_file)

    completion_memory_usage: dict[int, float] = {}
    execution_time: dict[int, float] = {}
    max_memory_usage: dict[int, float] = {}
    for dat_file in model_dir.glob("*.dat"):
        problem_idx = int(dat_file.stem)
        completion_memory_usage[problem_idx] = _calculate_memory_usage(dat_file)
        execution_time[problem_idx] = _calculate_runtime(dat_file)
        max_memory_usage[problem_idx] = _report_max_memory_usage(dat_file)

    total_execution_time = 0.0
    total_max_memory_usage = 0.0
    total_memory_usage = 0.0
    total_canonical_execution_time = 0.0
    total_canonical_max_memory_usage = 0.0
    total_canonical_memory_usage = 0.0
    total_codes = 0

    for idx, measured_memory in completion_memory_usage.items():
        canonical_memory = canonical_memory_usage.get(idx)
        canonical_runtime = canonical_execution_time.get(idx)
        canonical_max_memory_value = canonical_max_memory.get(idx)
        measured_runtime = execution_time.get(idx)
        measured_max_memory = max_memory_usage.get(idx)

        if (
            canonical_memory in (None, 0)
            or canonical_runtime in (None, 0)
            or canonical_max_memory_value in (None, 0)
            or measured_runtime is None
            or measured_max_memory is None
        ):
            continue

        total_execution_time += measured_runtime
        total_max_memory_usage += measured_max_memory
        total_memory_usage += measured_memory
        total_canonical_execution_time += canonical_runtime
        total_canonical_max_memory_usage += canonical_max_memory_value
        total_canonical_memory_usage += canonical_memory
        total_codes += 1

    if total_codes == 0:
        return EffiBenchOfficialSummary(
            model_name=model_name,
            num_tasks_requested=num_tasks_requested,
            num_tasks_measured=0,
            average_execution_time_seconds=None,
            normalized_execution_time=None,
            average_max_memory_mb=None,
            normalized_max_memory_usage=None,
            average_memory_usage_mb_seconds=None,
            normalized_memory_usage=None,
        )

    return EffiBenchOfficialSummary(
        model_name=model_name,
        num_tasks_requested=num_tasks_requested,
        num_tasks_measured=total_codes,
        average_execution_time_seconds=total_execution_time / total_codes,
        normalized_execution_time=total_execution_time / total_canonical_execution_time,
        average_max_memory_mb=total_max_memory_usage / total_codes,
        normalized_max_memory_usage=(
            total_max_memory_usage / total_canonical_max_memory_usage
        ),
        average_memory_usage_mb_seconds=total_memory_usage / total_codes,
        normalized_memory_usage=total_memory_usage / total_canonical_memory_usage,
    )


def read_effibench_dat_metrics(dat_file_path: str | Path) -> EffiBenchDatMetrics:
    path = Path(dat_file_path).resolve()
    return EffiBenchDatMetrics(
        runtime_seconds=_calculate_runtime(path),
        max_memory_mb=_report_max_memory_usage(path),
        memory_usage_mb_seconds=_calculate_memory_usage(path),
    )


def write_effibench_summary(summary: EffiBenchOfficialSummary, output_path: str | Path) -> Path:
    path = Path(output_path).resolve()
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(summary.to_dict(), indent=2), encoding="utf-8")
    return path


def _resolve_effibench_root(path: str | Path) -> Path:
    root = Path(path).resolve()
    expected = [
        root / "src" / "code_efficiency_calculator.py",
        root / "scripts" / "run_code.sh",
        root / "results",
        root / "dat_results",
    ]
    missing = [str(item) for item in expected if not item.exists()]
    if missing:
        raise FileNotFoundError(
            f"{root} does not look like an EffiBench checkout. Missing: {missing}"
        )
    return root


def _calculate_memory_usage(dat_file_path: Path) -> float:
    prev_time = 0.0
    prev_mem_mb = 0.0
    mem_time_mb_s = 0.0
    with dat_file_path.open(encoding="utf-8") as handle:
        next(handle, None)
        for line in handle:
            if "__main__." in line:
                continue
            parts = line.split()
            mem_in_mb = float(parts[1])
            timestamp = float(parts[2])
            if prev_time > 0:
                time_interval_s = timestamp - prev_time
                mem_time_mb_s += (prev_mem_mb + mem_in_mb) / 2 * time_interval_s
            prev_time = timestamp
            prev_mem_mb = mem_in_mb
    return mem_time_mb_s


def _calculate_runtime(dat_file_path: Path) -> float:
    start_time = float("inf")
    end_time = float("-inf")
    with dat_file_path.open(encoding="utf-8") as handle:
        next(handle, None)
        for line in handle:
            if "__main__." in line:
                continue
            parts = line.split()
            timestamp = float(parts[2])
            start_time = min(start_time, timestamp)
            end_time = max(end_time, timestamp)
    if start_time == float("inf") or end_time == float("-inf"):
        return 0.0
    return max(end_time - start_time, 0.0)


def _report_max_memory_usage(dat_file_path: Path) -> float:
    max_memory_usage = 0.0
    with dat_file_path.open(encoding="utf-8") as handle:
        next(handle, None)
        for line in handle:
            if "__main__." in line:
                continue
            parts = line.split()
            mem_in_mb = float(parts[1])
            max_memory_usage = max(max_memory_usage, mem_in_mb)
    return max_memory_usage
