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
from humaneval_pipeline.config import BenchmarkConfig, ExecutionConfig
from humaneval_pipeline.models import TaskRecord


class BenchmarkHarnessTests(unittest.TestCase):
    def setUp(self) -> None:
        self.benchmark = BenchmarkConfig(warmup_runs=0, measured_runs=1, poll_interval_seconds=0.01)
        self.execution = ExecutionConfig(
            compile_timeout_seconds=10,
            timeouts={"python": 1, "cpp": 2, "java": 2},
            java_runtime_flags=["-ea"],
        )

    def test_python_success(self) -> None:
        task = TaskRecord(
            problem_id="0",
            task_id="Python/0",
            language="python",
            prompt="def solve(x):\n",
            declaration="def solve(x):\n",
            canonical_solution="    return x + 1\n",
            test="assert solve(1) == 2\n",
            example_test="assert solve(1) == 2\n",
        )
        code = task.baseline_source
        result = evaluate_solution(
            task=task,
            code=code,
            source_path=Path("solution.py"),
            variant="before",
            objective=None,
            execution=self.execution,
            benchmark=self.benchmark,
        )
        self.assertTrue(result.correctness_pass)
        self.assertFalse(result.compile_error)
        self.assertEqual(len(result.samples), 1)

    @unittest.skipUnless(shutil.which("g++"), "g++ is required for C++ harness tests")
    def test_cpp_compile_error(self) -> None:
        task = TaskRecord(
            problem_id="1",
            task_id="CPP/1",
            language="cpp",
            prompt="#include <cassert>\nint solve(int x) {\n",
            declaration="int solve(int x) {\n",
            canonical_solution="    return x + 1;\n}\n",
            test="int main() { assert(solve(1) == 2); return 0; }\n",
            example_test="int main() { assert(solve(1) == 2); return 0; }\n",
        )
        bad_code = "#include <cassert>\nint solve(int x) {\n    return x + ;\n}\n"
        result = evaluate_solution(
            task=task,
            code=bad_code,
            source_path=Path("solution.cpp"),
            variant="after",
            objective="runtime",
            execution=self.execution,
            benchmark=self.benchmark,
        )
        self.assertFalse(result.correctness_pass)
        self.assertTrue(result.compile_error)

    @unittest.skipUnless(shutil.which("javac") and shutil.which("java"), "Java is required")
    def test_java_test_failure(self) -> None:
        task = TaskRecord(
            problem_id="2",
            task_id="Java/2",
            language="java",
            prompt=(
                "import java.util.*;\n\n"
                "class Solution {\n"
                "    public int solve(int x) {\n"
            ),
            declaration="public int solve(int x) {\n",
            canonical_solution="        return x + 1;\n    }\n}\n",
            test=(
                "public class Main {\n"
                "    public static void main(String[] args) {\n"
                "        Solution s = new Solution();\n"
                "        List<Boolean> correct = Arrays.asList(s.solve(1) == 2);\n"
                "        if (correct.contains(false)) {\n"
                "            throw new AssertionError();\n"
                "        }\n"
                "    }\n"
                "}\n"
            ),
            example_test="",
        )
        wrong_code = (
            "import java.util.*;\n\n"
            "class Solution {\n"
            "    public int solve(int x) {\n"
            "        return x;\n"
            "    }\n"
            "}\n"
        )
        result = evaluate_solution(
            task=task,
            code=wrong_code,
            source_path=Path("Solution.java"),
            variant="after",
            objective="memory",
            execution=self.execution,
            benchmark=self.benchmark,
        )
        self.assertFalse(result.correctness_pass)
        self.assertTrue(result.test_error)

    @unittest.skipUnless(shutil.which("javac") and shutil.which("java"), "Java is required")
    def test_java_success_with_split_main_file(self) -> None:
        task = TaskRecord(
            problem_id="4",
            task_id="Java/4",
            language="java",
            prompt=(
                "import java.util.*;\n\n"
                "class Solution {\n"
                "    public int solve(int x) {\n"
            ),
            declaration="public int solve(int x) {\n",
            canonical_solution="        return x + 1;\n    }\n}\n",
            test=(
                "public class Main {\n"
                "    public static void main(String[] args) {\n"
                "        Solution s = new Solution();\n"
                "        List<Boolean> correct = Arrays.asList(s.solve(1) == 2);\n"
                "        if (correct.contains(false)) {\n"
                "            throw new AssertionError();\n"
                "        }\n"
                "    }\n"
                "}\n"
            ),
            example_test="",
        )
        result = evaluate_solution(
            task=task,
            code=task.baseline_source,
            source_path=Path("Solution.java"),
            variant="before",
            objective=None,
            execution=self.execution,
            benchmark=self.benchmark,
        )
        self.assertTrue(result.correctness_pass)
        self.assertFalse(result.compile_error)

    def test_python_timeout(self) -> None:
        task = TaskRecord(
            problem_id="3",
            task_id="Python/3",
            language="python",
            prompt="def solve(x):\n",
            declaration="def solve(x):\n",
            canonical_solution="    return x + 1\n",
            test="assert solve(1) == 2\n",
            example_test="assert solve(1) == 2\n",
        )
        timeout_code = "def solve(x):\n    while True:\n        pass\n"
        result = evaluate_solution(
            task=task,
            code=timeout_code,
            source_path=Path("solution.py"),
            variant="after",
            objective="balanced",
            execution=self.execution,
            benchmark=self.benchmark,
        )
        self.assertFalse(result.correctness_pass)
        self.assertTrue(result.timeout)


if __name__ == "__main__":
    unittest.main()
