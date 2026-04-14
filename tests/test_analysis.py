from __future__ import annotations

import csv
import io
import os
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.analysis import _analysis_formula, run_analysis


def _analysis_deps_available() -> bool:
    os.environ.setdefault("PANDAS_NO_USE_NUMEXPR", "1")
    os.environ.setdefault("PANDAS_NO_USE_BOTTLENECK", "1")
    try:
        with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
            import matplotlib.pyplot  # noqa: F401
            import pandas  # noqa: F401
            import scipy  # noqa: F401
            import statsmodels  # noqa: F401
    except Exception:
        return False
    return True


class AnalysisTests(unittest.TestCase):
    def test_analysis_formula_adds_language_control_when_requested(self) -> None:
        self.assertEqual(
            _analysis_formula(False),
            "C(block_id, Sum) + C(objective, Sum) * C(prompt_detail, Sum)",
        )
        self.assertEqual(
            _analysis_formula(True),
            "C(block_id, Sum) + C(objective, Sum) * C(prompt_detail, Sum) + C(language, Sum)",
        )

    @unittest.skipUnless(_analysis_deps_available(), "analysis dependencies are unavailable")
    def test_analysis_generates_outputs_for_cpp_only_summary(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            config_path = root / "config.yaml"
            config_path.write_text(
                "\n".join(
                    [
                        "dataset_path: benchmark/human_eval_cpp.json",
                        "language: cpp",
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
                        "task_id",
                        "language",
                        "objective",
                        "prompt_detail",
                        "correctness_before",
                        "correctness_after",
                        "runtime_improvement_ratio",
                        "memory_improvement_ratio",
                        "memory_area_improvement_ratio",
                    ],
                )
                writer.writeheader()
                for task_id in ("0", "1"):
                    for objective, runtime_ratio, memory_ratio, memory_area_ratio in (
                        ("runtime", 1.2, 0.9, 0.95),
                        ("memory", 0.95, 1.3, 1.2),
                        ("balanced", 1.1, 1.1, 1.05),
                    ):
                        for prompt_detail in ("minimal", "detailed"):
                            writer.writerow(
                                {
                                    "task_id": task_id,
                                    "language": "cpp",
                                    "objective": objective,
                                    "prompt_detail": prompt_detail,
                                    "correctness_before": 1,
                                    "correctness_after": 1,
                                    "runtime_improvement_ratio": runtime_ratio,
                                    "memory_improvement_ratio": memory_ratio,
                                    "memory_area_improvement_ratio": memory_area_ratio,
                                }
                            )

            run_analysis(config_path)
            self.assertTrue((root / "results" / "analysis" / "runtime_improvement_ratio_anova.csv").exists())
            self.assertTrue((root / "results" / "analysis" / "memory_improvement_ratio_anova.csv").exists())
            self.assertTrue((root / "results" / "analysis" / "memory_area_improvement_ratio_anova.csv").exists())
            self.assertTrue(
                (
                    root
                    / "results"
                    / "analysis"
                    / "secondary_ge_5pct"
                    / "runtime_improvement_ratio_anova.csv"
                ).exists()
            )
            self.assertTrue(
                (
                    root
                    / "results"
                    / "analysis"
                    / "secondary_ge_5pct"
                    / "memory_improvement_ratio_anova.csv"
                ).exists()
            )
            self.assertTrue(
                (root / "results" / "analysis" / "secondary_ge_5pct" / "filter_summary.csv").exists()
            )

    @unittest.skipUnless(_analysis_deps_available(), "analysis dependencies are unavailable")
    def test_analysis_generates_outputs_for_mixed_language_summary(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            config_path = root / "config.yaml"
            config_path.write_text(
                "\n".join(
                    [
                        "dataset_path: benchmark/human_eval_cpp.json",
                        "language: cpp",
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
                        "task_id",
                        "language",
                        "objective",
                        "prompt_detail",
                        "correctness_before",
                        "correctness_after",
                        "runtime_improvement_ratio",
                        "memory_improvement_ratio",
                        "memory_area_improvement_ratio",
                    ],
                )
                writer.writeheader()
                for language in ("cpp", "python"):
                    for task_id in ("0", "1"):
                        for objective, runtime_ratio, memory_ratio, memory_area_ratio in (
                            ("runtime", 1.2, 0.9, 0.95),
                            ("memory", 0.95, 1.3, 1.2),
                            ("balanced", 1.1, 1.1, 1.05),
                        ):
                            for prompt_detail in ("minimal", "detailed"):
                                writer.writerow(
                                    {
                                        "task_id": task_id,
                                        "language": language,
                                        "objective": objective,
                                        "prompt_detail": prompt_detail,
                                        "correctness_before": 1,
                                        "correctness_after": 1,
                                        "runtime_improvement_ratio": runtime_ratio,
                                        "memory_improvement_ratio": memory_ratio,
                                        "memory_area_improvement_ratio": memory_area_ratio,
                                    }
                                )

            run_analysis(config_path)
            self.assertTrue((root / "results" / "analysis" / "correctness_rates.csv").exists())
            self.assertTrue(
                (root / "results" / "analysis" / "runtime_improvement_ratio_model_summary.txt").exists()
            )
            self.assertTrue(
                (
                    root
                    / "results"
                    / "analysis"
                    / "secondary_ge_5pct"
                    / "runtime_improvement_ratio_model_summary.txt"
                ).exists()
            )


if __name__ == "__main__":
    unittest.main()
