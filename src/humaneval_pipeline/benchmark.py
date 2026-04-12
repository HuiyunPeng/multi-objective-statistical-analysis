from __future__ import annotations

import os
import signal
import statistics
import subprocess
import time
from dataclasses import dataclass
from pathlib import Path

import psutil

from .config import BenchmarkConfig, ExecutionConfig
from .harnesses import get_harness
from .models import BenchmarkResult, BenchmarkSample, TaskRecord


@dataclass(frozen=True)
class CommandRunResult:
    runtime_seconds: float
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
    execution: ExecutionConfig,
    benchmark: BenchmarkConfig,
) -> BenchmarkResult:
    harness = get_harness(task.language)
    program = harness.prepare(task, code, execution)
    try:
        compile_result = program.compile_result
        if compile_result and not compile_result.success:
            return BenchmarkResult(
                problem_id=task.problem_id,
                task_id=task.task_id,
                language=task.language,
                variant=variant,
                objective=objective,
                source_path=str(source_path),
                correctness_pass=False,
                compile_error=True,
                test_error=False,
                timeout=compile_result.timeout,
                compile_stdout=compile_result.stdout,
                compile_stderr=compile_result.stderr,
                compile_returncode=compile_result.returncode,
            )

        timeout_seconds = execution.timeout_for(task.language)
        correctness_run = run_command_with_metrics(
            program.run_command,
            cwd=program.workdir,
            timeout_seconds=timeout_seconds,
            poll_interval_seconds=benchmark.poll_interval_seconds,
        )
        correctness_pass = not correctness_run.timeout and correctness_run.returncode == 0
        if not correctness_pass:
            return BenchmarkResult(
                problem_id=task.problem_id,
                task_id=task.task_id,
                language=task.language,
                variant=variant,
                objective=objective,
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

        for _ in range(benchmark.warmup_runs):
            warmup_run = run_command_with_metrics(
                program.run_command,
                cwd=program.workdir,
                timeout_seconds=timeout_seconds,
                poll_interval_seconds=benchmark.poll_interval_seconds,
            )
            if warmup_run.timeout or warmup_run.returncode != 0:
                return BenchmarkResult(
                    problem_id=task.problem_id,
                    task_id=task.task_id,
                    language=task.language,
                    variant=variant,
                    objective=objective,
                    source_path=str(source_path),
                    correctness_pass=True,
                    compile_error=False,
                    test_error=not warmup_run.timeout,
                    timeout=warmup_run.timeout,
                    compile_stdout=compile_result.stdout if compile_result else "",
                    compile_stderr=compile_result.stderr if compile_result else "",
                    compile_returncode=compile_result.returncode if compile_result else None,
                    correctness_stdout=correctness_run.stdout,
                    correctness_stderr=correctness_run.stderr,
                    correctness_returncode=correctness_run.returncode,
                )

        samples: list[BenchmarkSample] = []
        for repetition_index in range(benchmark.measured_runs):
            measured_run = run_command_with_metrics(
                program.run_command,
                cwd=program.workdir,
                timeout_seconds=timeout_seconds,
                poll_interval_seconds=benchmark.poll_interval_seconds,
            )
            if measured_run.timeout or measured_run.returncode != 0:
                return BenchmarkResult(
                    problem_id=task.problem_id,
                    task_id=task.task_id,
                    language=task.language,
                    variant=variant,
                    objective=objective,
                    source_path=str(source_path),
                    correctness_pass=True,
                    compile_error=False,
                    test_error=not measured_run.timeout,
                    timeout=measured_run.timeout,
                    compile_stdout=compile_result.stdout if compile_result else "",
                    compile_stderr=compile_result.stderr if compile_result else "",
                    compile_returncode=compile_result.returncode if compile_result else None,
                    correctness_stdout=correctness_run.stdout,
                    correctness_stderr=correctness_run.stderr,
                    correctness_returncode=correctness_run.returncode,
                )
            samples.append(
                BenchmarkSample(
                    repetition_index=repetition_index + 1,
                    runtime_seconds=measured_run.runtime_seconds,
                    peak_memory_bytes=measured_run.peak_memory_bytes,
                    returncode=measured_run.returncode,
                    stdout=measured_run.stdout,
                    stderr=measured_run.stderr,
                )
            )

        runtime_values = [sample.runtime_seconds for sample in samples]
        memory_values = [sample.peak_memory_bytes for sample in samples]
        runtime_mean = statistics.fmean(runtime_values)
        memory_mean = statistics.fmean(memory_values)
        runtime_std = statistics.stdev(runtime_values) if len(runtime_values) > 1 else 0.0
        memory_std = statistics.stdev(memory_values) if len(memory_values) > 1 else 0.0
        return BenchmarkResult(
            problem_id=task.problem_id,
            task_id=task.task_id,
            language=task.language,
            variant=variant,
            objective=objective,
            source_path=str(source_path),
            correctness_pass=True,
            compile_error=False,
            test_error=False,
            timeout=False,
            compile_stdout=compile_result.stdout if compile_result else "",
            compile_stderr=compile_result.stderr if compile_result else "",
            compile_returncode=compile_result.returncode if compile_result else None,
            correctness_stdout=correctness_run.stdout,
            correctness_stderr=correctness_run.stderr,
            correctness_returncode=correctness_run.returncode,
            runtime_mean=runtime_mean,
            runtime_std=runtime_std,
            runtime_cv=(runtime_std / runtime_mean) if runtime_mean else None,
            memory_mean=memory_mean,
            memory_std=memory_std,
            memory_cv=(memory_std / memory_mean) if memory_mean else None,
            samples=samples,
        )
    finally:
        program.cleanup()


def run_command_with_metrics(
    command: list[str],
    cwd: Path,
    timeout_seconds: int,
    poll_interval_seconds: float,
) -> CommandRunResult:
    start = time.perf_counter()
    process = subprocess.Popen(
        command,
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
    runtime_seconds = time.perf_counter() - start
    if timed_out:
        returncode = process.returncode if process.returncode is not None else -signal.SIGKILL
    else:
        returncode = process.returncode or 0

    return CommandRunResult(
        runtime_seconds=runtime_seconds,
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
