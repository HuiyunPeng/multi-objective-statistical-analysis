from __future__ import annotations

import csv
import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.analysis import run_analysis


@unittest.skipUnless(importlib.util.find_spec("statsmodels"), "statsmodels is not installed")
class AnalysisTests(unittest.TestCase):
    def test_analysis_generates_outputs_for_synthetic_summary(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            config_path = root / "config.yaml"
            config_path.write_text(
                "\n".join(
                    [
                        "dataset:",
                        "  source_urls: ['https://example.com/{language}.jsonl']",
                        "paths:",
                        "  summary_csv: 'results/analysis_ready.csv'",
                        "  analysis_dir: 'results/analysis'",
                    ]
                ),
                encoding="utf-8",
            )

            summary_path = root / "results" / "analysis_ready.csv"
            summary_path.parent.mkdir(parents=True, exist_ok=True)
            with summary_path.open("w", encoding="utf-8", newline="") as handle:
                writer = csv.DictWriter(
                    handle,
                    fieldnames=[
                        "problem_id",
                        "language",
                        "objective",
                        "correctness_before",
                        "correctness_after",
                        "runtime_improvement_ratio",
                        "memory_improvement_ratio",
                    ],
                )
                writer.writeheader()
                for problem_id in ("0", "1"):
                    for language in ("python", "cpp", "java"):
                        for objective, runtime_ratio, memory_ratio in (
                            ("runtime", 1.2, 0.9),
                            ("memory", 0.95, 1.3),
                            ("balanced", 1.1, 1.1),
                        ):
                            writer.writerow(
                                {
                                    "problem_id": problem_id,
                                    "language": language,
                                    "objective": objective,
                                    "correctness_before": 1,
                                    "correctness_after": 1,
                                    "runtime_improvement_ratio": runtime_ratio,
                                    "memory_improvement_ratio": memory_ratio,
                                }
                            )

            run_analysis(config_path)
            self.assertTrue((root / "results" / "analysis" / "runtime_improvement_ratio_anova.csv").exists())
            self.assertTrue((root / "results" / "analysis" / "memory_improvement_ratio_anova.csv").exists())


if __name__ == "__main__":
    unittest.main()
