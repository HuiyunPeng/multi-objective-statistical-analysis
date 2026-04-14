from __future__ import annotations

import shutil
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

from .config import ExperimentConfig
from .models import TaskRecord


@dataclass(frozen=True)
class CompileResult:
    success: bool
    returncode: int | None
    stdout: str
    stderr: str
    timeout: bool


@dataclass
class PreparedProgram:
    language: str
    workdir: Path
    run_command: list[str]
    source_file: Path
    compile_result: CompileResult | None = None

    def cleanup(self) -> None:
        shutil.rmtree(self.workdir, ignore_errors=True)


class BaseHarness:
    language: str

    def prepare_correctness(
        self, task: TaskRecord, code: str, config: ExperimentConfig
    ) -> PreparedProgram:
        raise NotImplementedError

    def prepare_performance(
        self, task: TaskRecord, code: str, config: ExperimentConfig
    ) -> PreparedProgram:
        raise NotImplementedError

    @staticmethod
    def _tempdir(language: str) -> Path:
        return Path(tempfile.mkdtemp(prefix=f"humaneval_{language}_"))

    @staticmethod
    def _combined_source(code: str, harness_code: str) -> str:
        return f"{code.rstrip()}\n\n{harness_code.rstrip()}\n"


class CppHarness(BaseHarness):
    language = "cpp"

    def prepare_correctness(
        self, task: TaskRecord, code: str, config: ExperimentConfig
    ) -> PreparedProgram:
        return self._prepare(task, code, task.test_code, config)

    def prepare_performance(
        self, task: TaskRecord, code: str, config: ExperimentConfig
    ) -> PreparedProgram:
        if not task.performance_test_code:
            raise ValueError(f"Task {task.task_id} does not define performance_test_code.")
        return self._prepare(task, code, task.performance_test_code, config)

    def _prepare(
        self,
        task: TaskRecord,
        code: str,
        harness_code: str,
        config: ExperimentConfig,
    ) -> PreparedProgram:
        workdir = self._tempdir(self.language)
        source_file = workdir / "solution.cpp"
        executable = workdir / "solution.out"
        source_file.write_text(self._combined_source(code, harness_code), encoding="utf-8")

        command = [
            config.toolchain.cpp_compiler,
            *config.toolchain.cpp_compile_flags,
            str(source_file),
            "-o",
            str(executable),
            *config.toolchain.cpp_link_flags,
        ]
        compile_result = _run_compile(command, workdir, config.compile_timeout)
        return PreparedProgram(
            language=self.language,
            workdir=workdir,
            run_command=[str(executable)],
            source_file=source_file,
            compile_result=compile_result,
        )


def _run_compile(command: list[str], cwd: Path, timeout_seconds: int) -> CompileResult:
    try:
        completed = subprocess.run(
            command,
            cwd=cwd,
            capture_output=True,
            text=True,
            timeout=timeout_seconds,
            check=False,
        )
    except subprocess.TimeoutExpired as exc:
        return CompileResult(
            success=False,
            returncode=None,
            stdout=exc.stdout or "",
            stderr=exc.stderr or "",
            timeout=True,
        )

    return CompileResult(
        success=completed.returncode == 0,
        returncode=completed.returncode,
        stdout=completed.stdout,
        stderr=completed.stderr,
        timeout=False,
    )


def get_harness(language: str) -> BaseHarness:
    if language == "cpp":
        return CppHarness()
    raise NotImplementedError(
        f"Language harness for {language!r} is not implemented yet. "
        "Add a dataset mapping and harness implementation for that language."
    )
