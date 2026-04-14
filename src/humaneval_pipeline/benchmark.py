from __future__ import annotations

import os
import signal
import shutil
import statistics
import subprocess
import tempfile
import time
from dataclasses import dataclass
from pathlib import Path

import psutil

from .config import ExperimentConfig
from .harnesses import get_harness
from .models import BenchmarkResult, BenchmarkSample, TaskRecord

GNU_TIME_PATH = shutil.which("/usr/bin/time") or shutil.which("time")
GNU_TIME_MEMORY_FORMAT = "%M"
POLL_INTERVAL_SECONDS = 0.01


@dataclass(frozen=True)
class CommandRunResult:
    runtime_milliseconds: float
    peak_memory_bytes: int
    returncode: int
    stdout: str
    stderr: str
    timeout: bool


def evaluate_solution(
    task: TaskRecord,
    code: str,
    source_path: Path,
    variant: str,
    objective: str | None,
    prompt_detail: str | None,
    config: ExperimentConfig,
) -> BenchmarkResult:
    harness = get_harness(task.language)
    correctness_program = harness.prepare_correctness(task, code, config)
    try:
        compile_result = correctness_program.compile_result
        if compile_result and not compile_result.success:
            return BenchmarkResult(
                task_id=task.task_id,
                language=task.language,
                variant=variant,
                objective=objective,
                prompt_detail=prompt_detail,
                source_path=str(source_path),
                correctness_pass=False,
                compile_error=True,
                test_error=False,
                timeout=compile_result.timeout,
                compile_stdout=compile_result.stdout,
                compile_stderr=compile_result.stderr,
                compile_returncode=compile_result.returncode,
            )

        correctness_run = run_command_with_metrics(
            correctness_program.run_command,
            cwd=correctness_program.workdir,
            timeout_seconds=config.run_timeout,
            poll_interval_seconds=POLL_INTERVAL_SECONDS,
        )
        if correctness_run.timeout or correctness_run.returncode != 0:
            return BenchmarkResult(
                task_id=task.task_id,
                language=task.language,
                variant=variant,
                objective=objective,
                prompt_detail=prompt_detail,
                source_path=str(source_path),
                correctness_pass=False,
                compile_error=False,
                test_error=not correctness_run.timeout,
                timeout=correctness_run.timeout,
                compile_stdout=compile_result.stdout if compile_result else "",
                compile_stderr=compile_result.stderr if compile_result else "",
                compile_returncode=compile_result.returncode if compile_result else None,
                correctness_stdout=correctness_run.stdout,
                correctness_stderr=correctness_run.stderr,
                correctness_returncode=correctness_run.returncode,
            )
    finally:
        correctness_program.cleanup()

    if not task.performance_test_code:
        return BenchmarkResult(
            task_id=task.task_id,
            language=task.language,
            variant=variant,
            objective=objective,
            prompt_detail=prompt_detail,
            source_path=str(source_path),
            correctness_pass=True,
            compile_error=False,
            test_error=False,
            timeout=False,
        )

    performance_program = harness.prepare_performance(task, code, config)
    try:
        performance_compile = performance_program.compile_result
        if performance_compile and not performance_compile.success:
            return BenchmarkResult(
                task_id=task.task_id,
                language=task.language,
                variant=variant,
                objective=objective,
                prompt_detail=prompt_detail,
                source_path=str(source_path),
                correctness_pass=True,
                compile_error=True,
                test_error=False,
                timeout=performance_compile.timeout,
                compile_stdout=performance_compile.stdout,
                compile_stderr=performance_compile.stderr,
                compile_returncode=performance_compile.returncode,
            )

        for _ in range(config.warmup_runs):
            warmup_run = run_command_with_metrics(
                performance_program.run_command,
                cwd=performance_program.workdir,
                timeout_seconds=config.run_timeout,
                poll_interval_seconds=POLL_INTERVAL_SECONDS,
            )
            if warmup_run.timeout or warmup_run.returncode != 0:
                return BenchmarkResult(
                    task_id=task.task_id,
                    language=task.language,
                    variant=variant,
                    objective=objective,
                    prompt_detail=prompt_detail,
                    source_path=str(source_path),
                    correctness_pass=True,
                    compile_error=False,
                    test_error=not warmup_run.timeout,
                    timeout=warmup_run.timeout,
                    compile_stdout=performance_compile.stdout if performance_compile else "",
                    compile_stderr=performance_compile.stderr if performance_compile else "",
                    compile_returncode=performance_compile.returncode if performance_compile else None,
                )

        samples: list[BenchmarkSample] = []
        for repetition_index in range(config.num_repetitions):
            measured_run = run_command_with_metrics(
                performance_program.run_command,
                cwd=performance_program.workdir,
                timeout_seconds=config.run_timeout,
                poll_interval_seconds=POLL_INTERVAL_SECONDS,
            )
            if measured_run.timeout or measured_run.returncode != 0:
                return BenchmarkResult(
                    task_id=task.task_id,
                    language=task.language,
                    variant=variant,
                    objective=objective,
                    prompt_detail=prompt_detail,
                    source_path=str(source_path),
                    correctness_pass=True,
                    compile_error=False,
                    test_error=not measured_run.timeout,
                    timeout=measured_run.timeout,
                    compile_stdout=performance_compile.stdout if performance_compile else "",
                    compile_stderr=performance_compile.stderr if performance_compile else "",
                    compile_returncode=performance_compile.returncode if performance_compile else None,
                )

            samples.append(
                BenchmarkSample(
                    repetition_index=repetition_index + 1,
                    runtime_milliseconds=measured_run.runtime_milliseconds,
                    peak_memory_bytes=measured_run.peak_memory_bytes,
                    returncode=measured_run.returncode,
                    stdout=measured_run.stdout,
                    stderr=measured_run.stderr,
                )
            )

        runtime_values = [sample.runtime_milliseconds for sample in samples]
        memory_values = [sample.peak_memory_bytes for sample in samples]
        runtime_mean_ms = statistics.fmean(runtime_values)
        memory_mean = statistics.fmean(memory_values)
        runtime_std_ms = statistics.stdev(runtime_values) if len(runtime_values) > 1 else 0.0
        memory_std = statistics.stdev(memory_values) if len(memory_values) > 1 else 0.0
        return BenchmarkResult(
            task_id=task.task_id,
            language=task.language,
            variant=variant,
            objective=objective,
            prompt_detail=prompt_detail,
            source_path=str(source_path),
            correctness_pass=True,
            compile_error=False,
            test_error=False,
            timeout=False,
            compile_stdout=performance_compile.stdout if performance_compile else "",
            compile_stderr=performance_compile.stderr if performance_compile else "",
            compile_returncode=performance_compile.returncode if performance_compile else None,
            runtime_mean_ms=runtime_mean_ms,
            runtime_std_ms=runtime_std_ms,
            runtime_cv=(runtime_std_ms / runtime_mean_ms) if runtime_mean_ms else None,
            memory_mean=memory_mean,
            memory_std=memory_std,
            memory_cv=(memory_std / memory_mean) if memory_mean else None,
            samples=samples,
        )
    finally:
        performance_program.cleanup()


def run_command_with_metrics(
    command: list[str],
    cwd: Path,
    timeout_seconds: int,
    poll_interval_seconds: float,
) -> CommandRunResult:
    instrumented_command = command
    memory_file_path: Path | None = None
    if GNU_TIME_PATH:
        memory_file_path = Path(
            tempfile.mkstemp(prefix="memory_", suffix=".txt", dir=cwd)[1]
        )
        instrumented_command = [
            GNU_TIME_PATH,
            "-f",
            GNU_TIME_MEMORY_FORMAT,
            "-o",
            str(memory_file_path),
            *command,
        ]

    start = time.perf_counter()
    process = subprocess.Popen(
        instrumented_command,
        cwd=cwd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        start_new_session=True,
    )
    root_process = psutil.Process(process.pid)
    peak_memory_bytes = 0
    timed_out = False

    while True:
        returncode = process.poll()
        peak_memory_bytes = max(peak_memory_bytes, _tree_rss(root_process))
        if returncode is not None:
            break
        if time.perf_counter() - start > timeout_seconds:
            timed_out = True
            _terminate_process_group(process)
            break
        time.sleep(poll_interval_seconds)

    stdout, stderr = process.communicate()
    runtime_milliseconds = (time.perf_counter() - start) * 1000.0
    if timed_out:
        returncode = process.returncode if process.returncode is not None else -signal.SIGKILL
    else:
        returncode = process.returncode or 0

    peak_memory_bytes = _read_gnu_time_peak_memory(memory_file_path) or peak_memory_bytes
    if memory_file_path is not None:
        memory_file_path.unlink(missing_ok=True)

    return CommandRunResult(
        runtime_milliseconds=runtime_milliseconds,
        peak_memory_bytes=peak_memory_bytes,
        returncode=returncode,
        stdout=stdout,
        stderr=stderr,
        timeout=timed_out,
    )


def _tree_rss(root_process: psutil.Process) -> int:
    processes = [root_process]
    try:
        processes.extend(root_process.children(recursive=True))
    except (psutil.Error, PermissionError):
        pass

    total = 0
    for process in processes:
        try:
            total += int(process.memory_info().rss)
        except (psutil.Error, PermissionError):
            continue
    return total


def _terminate_process_group(process: subprocess.Popen[str]) -> None:
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except OSError:
        process.kill()


def _read_gnu_time_peak_memory(memory_file_path: Path | None) -> int | None:
    if memory_file_path is None or not memory_file_path.exists():
        return None

    raw_value = memory_file_path.read_text(encoding="utf-8").strip()
    if not raw_value:
        return None

    try:
        peak_kib = int(raw_value)
    except ValueError:
        return None
    return peak_kib * 1024
