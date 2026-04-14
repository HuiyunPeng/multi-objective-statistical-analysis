from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.effibench_official import (
    stage_effibench_results,
    summarize_official_effibench_results,
)


class EffiBenchOfficialTests(unittest.TestCase):
    def test_stage_effibench_results_applies_limit(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            effibench_root = self._make_effibench_root(root / "EffiBench")
            input_json = root / "input.json"
            input_json.write_text(
                json.dumps([self._result_row(3), self._result_row(4)]),
                encoding="utf-8",
            )

            staged_path, staged_count = stage_effibench_results(
                input_json=input_json,
                effibench_root=effibench_root,
                model_name="demo-model",
                limit=1,
            )

            self.assertEqual(staged_path, effibench_root / "results" / "demo-model.json")
            self.assertEqual(staged_count, 1)
            staged_rows = json.loads(staged_path.read_text(encoding="utf-8"))
            self.assertEqual(len(staged_rows), 1)
            self.assertEqual(staged_rows[0]["problem_idx"], 3)

    def test_summarize_official_effibench_results_matches_expected_ratios(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            effibench_root = self._make_effibench_root(root / "EffiBench")
            canonical_dir = effibench_root / "dat_results" / "canonical_solution"
            model_dir = effibench_root / "dat_results" / "demo-model"
            model_dir.mkdir(parents=True, exist_ok=True)

            (canonical_dir / "3.dat").write_text(
                "CMDLINE test\nMEM 10 1.0\nMEM 10 2.0\n",
                encoding="utf-8",
            )
            (model_dir / "3.dat").write_text(
                "CMDLINE test\nMEM 10 1.0\nMEM 20 2.5\n",
                encoding="utf-8",
            )

            summary = summarize_official_effibench_results(
                effibench_root=effibench_root,
                model_name="demo-model",
                num_tasks_requested=1,
            )

            self.assertEqual(summary.num_tasks_measured, 1)
            self.assertAlmostEqual(summary.average_execution_time_seconds or 0.0, 1.5)
            self.assertAlmostEqual(summary.normalized_execution_time or 0.0, 1.5)
            self.assertAlmostEqual(summary.average_max_memory_mb or 0.0, 20.0)
            self.assertAlmostEqual(summary.normalized_max_memory_usage or 0.0, 2.0)
            self.assertAlmostEqual(summary.average_memory_usage_mb_seconds or 0.0, 22.5)
            self.assertAlmostEqual(summary.normalized_memory_usage or 0.0, 2.25)

    @staticmethod
    def _make_effibench_root(path: Path) -> Path:
        (path / "src").mkdir(parents=True, exist_ok=True)
        (path / "scripts").mkdir(parents=True, exist_ok=True)
        (path / "results").mkdir(parents=True, exist_ok=True)
        (path / "dat_results" / "canonical_solution").mkdir(parents=True, exist_ok=True)
        (path / "src" / "code_efficiency_calculator.py").write_text("", encoding="utf-8")
        (path / "scripts" / "run_code.sh").write_text("", encoding="utf-8")
        return path

    @staticmethod
    def _result_row(problem_idx: int) -> dict[str, object]:
        return {
            "problem_idx": problem_idx,
            "task_name": f"Task {problem_idx}",
            "completion": "class Solution:\n    pass\n",
            "canonical_solution": "class Solution:\n    pass\n",
            "small_test_cases": "solution = Solution()\n",
            "test_case": "solution = Solution()\n",
        }


if __name__ == "__main__":
    unittest.main()
