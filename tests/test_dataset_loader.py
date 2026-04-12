from __future__ import annotations

import sys
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.dataset_loader import HumanEvalXLoader


class DatasetLoaderTests(unittest.TestCase):
    def test_normalize_problem_id_with_language_prefix(self) -> None:
        self.assertEqual(HumanEvalXLoader.normalize_problem_id("Python/0"), "0")
        self.assertEqual(HumanEvalXLoader.normalize_problem_id("CPP/17"), "17")
        self.assertEqual(HumanEvalXLoader.normalize_problem_id("Java/103"), "103")

    def test_normalize_problem_id_without_prefix(self) -> None:
        self.assertEqual(HumanEvalXLoader.normalize_problem_id("HumanEval_0"), "HumanEval_0")


if __name__ == "__main__":
    unittest.main()
