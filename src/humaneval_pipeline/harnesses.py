from __future__ import annotations

import re
import shutil
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

from .config import ExecutionConfig
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

    def prepare(self, task: TaskRecord, code: str, execution: ExecutionConfig) -> PreparedProgram:
        raise NotImplementedError

    @staticmethod
    def _tempdir(language: str) -> Path:
        return Path(tempfile.mkdtemp(prefix=f"humaneval_{language}_"))

    @staticmethod
    def _combined_source(code: str, test_code: str) -> str:
        return f"{code.rstrip()}\n\n{test_code.rstrip()}\n"


class PythonHarness(BaseHarness):
    language = "python"

    def prepare(self, task: TaskRecord, code: str, execution: ExecutionConfig) -> PreparedProgram:
        workdir = self._tempdir(self.language)
        source_file = workdir / "solution.py"
        source_file.write_text(self._combined_source(code, task.test), encoding="utf-8")
        return PreparedProgram(
            language=self.language,
            workdir=workdir,
            run_command=[execution.python_executable, str(source_file)],
            source_file=source_file,
        )


class CppHarness(BaseHarness):
    language = "cpp"

    def prepare(self, task: TaskRecord, code: str, execution: ExecutionConfig) -> PreparedProgram:
        workdir = self._tempdir(self.language)
        source_file = workdir / "solution.cpp"
        executable = workdir / "solution.out"
        source_file.write_text(self._combined_source(code, task.test), encoding="utf-8")

        command = [
            execution.cpp_compiler,
            *execution.cpp_compile_flags,
            str(source_file),
            "-o",
            str(executable),
            *execution.cpp_link_flags,
        ]
        compile_result = _run_compile(command, workdir, execution.compile_timeout_seconds)
        return PreparedProgram(
            language=self.language,
            workdir=workdir,
            run_command=[str(executable)],
            source_file=source_file,
            compile_result=compile_result,
        )


class JavaHarness(BaseHarness):
    language = "java"

    CLASS_PATTERN = re.compile(r"\b(?:public\s+)?class\s+([A-Za-z_][A-Za-z0-9_]*)")

    def prepare(self, task: TaskRecord, code: str, execution: ExecutionConfig) -> PreparedProgram:
        workdir = self._tempdir(self.language)
        combined_source = self._combined_source(code, task.test)
        class_name = self._class_name(combined_source)
        source_file = workdir / f"{class_name}.java"
        source_file.write_text(combined_source, encoding="utf-8")

        command = [execution.java_compiler, *execution.java_compile_flags, source_file.name]
        compile_result = _run_compile(command, workdir, execution.compile_timeout_seconds)
        return PreparedProgram(
            language=self.language,
            workdir=workdir,
            run_command=[execution.java_runtime, *execution.java_runtime_flags, class_name],
            source_file=source_file,
            compile_result=compile_result,
        )

    @classmethod
    def _class_name(cls, source: str) -> str:
        match = cls.CLASS_PATTERN.search(source)
        if match:
            return match.group(1)
        return "Problem"


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
    if language == "python":
        return PythonHarness()
    if language == "cpp":
        return CppHarness()
    if language == "java":
        return JavaHarness()
    raise ValueError(f"Unsupported language: {language}")
