from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.pipeline import _should_rerun_signature_skipped_case
from humaneval_pipeline.utils import write_json


class PipelineResumeTests(unittest.TestCase):
    def test_reruns_prior_signature_skip_once_metadata_is_valid(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            eval_path = Path(tmpdir) / "optimized.json"
            write_json(
                eval_path,
                {
                    "correctness_stderr": "Signature validation failed before execution.",
                    "correctness_pass": False,
                },
            )
            metadata = {"signature_valid": True}
            self.assertTrue(_should_rerun_signature_skipped_case(eval_path, metadata))

    def test_does_not_rerun_non_signature_failures(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            eval_path = Path(tmpdir) / "optimized.json"
            write_json(
                eval_path,
                {
                    "correctness_stderr": "AssertionError",
                    "correctness_pass": False,
                },
            )
            metadata = {"signature_valid": True}
            self.assertFalse(_should_rerun_signature_skipped_case(eval_path, metadata))


if __name__ == "__main__":
    unittest.main()
