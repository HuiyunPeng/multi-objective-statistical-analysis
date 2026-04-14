from __future__ import annotations

import shutil
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.benchmark import evaluate_solution
from humaneval_pipeline.config import ExperimentConfig
from humaneval_pipeline.models import TaskRecord


@unittest.skipUnless(shutil.which("g++"), "g++ is required for C++ harness tests")
class BenchmarkHarnessTests(unittest.TestCase):
    def test_cpp_success_collects_metrics(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = self._config(Path(tmpdir), warmup_runs=1, num_repetitions=1, run_timeout=2)
            task = self._task(
                function_code="#include <cassert>\nint solve(int x) { return x + 1; }\n",
                test_code="int main() { assert(solve(1) == 2); return 0; }\n",
                performance_test_code="int main() { for (int i = 0; i < 10000; ++i) solve(i); return 0; }\n",
            )

            result = evaluate_solution(
                task=task,
                code=task.function_code,
                source_path=Path("solution.cpp"),
                variant="before",
                objective=None,
                prompt_detail=None,
                config=config,
            )

            self.assertTrue(result.correctness_pass)
            self.assertFalse(result.compile_error)
            self.assertEqual(len(result.samples), 1)
            self.assertIsNotNone(result.runtime_mean_ms)
            self.assertIsNotNone(result.memory_mean)
            self.assertGreater(result.runtime_mean_ms, 0.0)
            self.assertGreater(result.memory_mean, 0.0)

    def test_cpp_compile_error(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = self._config(Path(tmpdir), warmup_runs=0, num_repetitions=1, run_timeout=2)
            task = self._task(
                function_code="#include <cassert>\nint solve(int x) { return x + 1; }\n",
                test_code="int main() { assert(solve(1) == 2); return 0; }\n",
                performance_test_code="int main() { return 0; }\n",
            )
            bad_code = "#include <cassert>\nint solve(int x) { return x + ; }\n"

            result = evaluate_solution(
                task=task,
                code=bad_code,
                source_path=Path("solution.cpp"),
                variant="after",
                objective="runtime",
                prompt_detail="minimal",
                config=config,
            )

            self.assertFalse(result.correctness_pass)
            self.assertTrue(result.compile_error)
            self.assertIsNone(result.runtime_mean_ms)

    def test_cpp_timeout_during_correctness(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = self._config(Path(tmpdir), warmup_runs=0, num_repetitions=1, run_timeout=1)
            task = self._task(
                function_code="#include <cassert>\nint solve(int x) { while (true) {} return x; }\n",
                test_code="int main() { solve(1); return 0; }\n",
                performance_test_code="int main() { return 0; }\n",
            )

            result = evaluate_solution(
                task=task,
                code=task.function_code,
                source_path=Path("solution.cpp"),
                variant="after",
                objective="balanced",
                prompt_detail="detailed",
                config=config,
            )

            self.assertFalse(result.correctness_pass)
            self.assertTrue(result.timeout)
            self.assertEqual(result.samples, [])

    def test_no_performance_metrics_when_correctness_fails(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = self._config(Path(tmpdir), warmup_runs=0, num_repetitions=1, run_timeout=2)
            task = self._task(
                function_code="#include <cassert>\nint solve(int x) { return x; }\n",
                test_code="int main() { assert(solve(1) == 2); return 0; }\n",
                performance_test_code="int main() { for (int i = 0; i < 10000; ++i) solve(i); return 0; }\n",
            )

            result = evaluate_solution(
                task=task,
                code=task.function_code,
                source_path=Path("solution.cpp"),
                variant="after",
                objective="memory",
                prompt_detail="minimal",
                config=config,
            )

            self.assertFalse(result.correctness_pass)
            self.assertIsNone(result.runtime_mean_ms)
            self.assertIsNone(result.memory_mean)
            self.assertEqual(result.samples, [])

    @staticmethod
    def _config(
        project_root: Path, warmup_runs: int, num_repetitions: int, run_timeout: int
    ) -> ExperimentConfig:
        config = ExperimentConfig(
            dataset_path="benchmark.json",
            language="cpp",
            objectives=["runtime"],
            prompt_detail_levels=["minimal"],
            warmup_runs=warmup_runs,
            num_repetitions=num_repetitions,
            compile_timeout=10,
            run_timeout=run_timeout,
            project_root=project_root,
        )
        config.ensure_directories()
        return config

    @staticmethod
    def _task(function_code: str, test_code: str, performance_test_code: str) -> TaskRecord:
        return TaskRecord(
            task_id="0",
            language="cpp",
            entry_point="solve",
            function_code=function_code,
            test_code=test_code,
            stress_test="int main() { return 1; }\n",
            cpp_stress_test=performance_test_code,
            performance_test_code=performance_test_code,
        )


if __name__ == "__main__":
    unittest.main()
