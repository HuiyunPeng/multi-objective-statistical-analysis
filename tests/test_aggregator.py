from __future__ import annotations

import csv
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.aggregator import write_aggregated_results
from humaneval_pipeline.artifact_paths import evaluation_path, generation_metadata_path
from humaneval_pipeline.config import ExperimentConfig
from humaneval_pipeline.models import TaskRecord
from humaneval_pipeline.utils import write_json


class AggregatorTests(unittest.TestCase):
    def test_summary_includes_prompt_detail_rows_and_reused_baseline_metrics(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                objectives=["runtime", "memory"],
                prompt_detail_levels=["minimal", "detailed"],
                project_root=root,
            )
            config.ensure_directories()

            task = TaskRecord(
                task_id="0",
                language="cpp",
                entry_point="solve",
                function_code="int solve(int x) { return x + 1; }\n",
                test_code="int main() { return solve(1) == 2 ? 0 : 1; }\n",
                performance_test_code="int main() { return 0; }\n",
            )
            tasks = [task]

            before_payload = {
                "task_id": "0",
                "language": "cpp",
                "variant": "before",
                "objective": None,
                "prompt_detail": None,
                "source_path": str(root / "generated_code" / "baseline.cpp"),
                "correctness_pass": True,
                "compile_error": False,
                "test_error": False,
                "timeout": False,
                "runtime_mean_ms": 10.0,
                "runtime_std_ms": 1.0,
                "runtime_cv": 0.1,
                "memory_mean": 100.0,
                "memory_std": 10.0,
                "memory_cv": 0.1,
                "samples": [
                    {
                        "repetition_index": 1,
                        "runtime_milliseconds": 10.0,
                        "peak_memory_bytes": 100,
                        "returncode": 0,
                        "stdout": "",
                        "stderr": "",
                    }
                ],
            }
            write_json(evaluation_path(config, "baseline", "0", "cpp"), before_payload)

            for objective in config.objectives:
                for prompt_detail in config.prompt_detail_levels:
                    after_payload = {
                        **before_payload,
                        "variant": "after",
                        "objective": objective,
                        "prompt_detail": prompt_detail,
                        "source_path": str(root / "generated_code" / f"{objective}_{prompt_detail}.cpp"),
                        "runtime_mean_ms": 5.0,
                        "memory_mean": 50.0,
                    }
                    write_json(
                        evaluation_path(
                            config,
                            "optimized",
                            "0",
                            "cpp",
                            objective,
                            prompt_detail,
                        ),
                        after_payload,
                    )
                    write_json(
                        generation_metadata_path(config, "0", "cpp", objective, prompt_detail),
                        {
                            "task_id": "0",
                            "language": "cpp",
                            "objective": objective,
                            "prompt_detail": prompt_detail,
                            "prompt_path": f"prompts/{objective}/{prompt_detail}/cpp/0.txt",
                            "raw_text_path": f"results/raw_responses/{objective}/{prompt_detail}/cpp/0.txt",
                            "raw_json_path": f"results/raw_responses/{objective}/{prompt_detail}/cpp/0.json",
                            "cleaned_code_path": f"generated_code/optimized/{objective}/{prompt_detail}/cpp/0.cpp",
                            "signature_valid": True,
                            "model_name": "gpt-5.4",
                            "from_cache": True,
                        },
                    )

            _, summary_path = write_aggregated_results(config, tasks)
            with summary_path.open("r", encoding="utf-8", newline="") as handle:
                rows = list(csv.DictReader(handle))

            self.assertEqual(len(rows), 4)
            self.assertEqual({row["prompt_detail"] for row in rows}, {"minimal", "detailed"})
            self.assertEqual({row["objective"] for row in rows}, {"runtime", "memory"})
            self.assertTrue(all(row["runtime_improvement_ratio"] == "2.0" for row in rows))

    def test_summary_leaves_improvement_ratio_blank_when_after_metrics_are_missing(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                objectives=["runtime"],
                prompt_detail_levels=["minimal"],
                project_root=root,
            )
            config.ensure_directories()

            task = TaskRecord(
                task_id="0",
                language="cpp",
                entry_point="solve",
                function_code="int solve(int x) { return x + 1; }\n",
                test_code="int main() { return solve(1) == 2 ? 0 : 1; }\n",
                performance_test_code="int main() { return 0; }\n",
            )
            tasks = [task]

            before_payload = {
                "task_id": "0",
                "language": "cpp",
                "variant": "before",
                "objective": None,
                "prompt_detail": None,
                "source_path": str(root / "generated_code" / "baseline.cpp"),
                "correctness_pass": True,
                "compile_error": False,
                "test_error": False,
                "timeout": False,
                "runtime_mean_ms": 10.0,
                "memory_mean": 100.0,
                "samples": [],
            }
            after_payload = {
                **before_payload,
                "variant": "after",
                "objective": "runtime",
                "prompt_detail": "minimal",
                "runtime_mean_ms": None,
                "memory_mean": None,
            }
            write_json(evaluation_path(config, "baseline", "0", "cpp"), before_payload)
            write_json(
                evaluation_path(config, "optimized", "0", "cpp", "runtime", "minimal"),
                after_payload,
            )
            write_json(
                generation_metadata_path(config, "0", "cpp", "runtime", "minimal"),
                {
                    "task_id": "0",
                    "language": "cpp",
                    "objective": "runtime",
                    "prompt_detail": "minimal",
                    "prompt_path": "prompts/runtime/minimal/cpp/0.txt",
                    "raw_text_path": "results/raw_responses/runtime/minimal/cpp/0.txt",
                    "raw_json_path": "results/raw_responses/runtime/minimal/cpp/0.json",
                    "cleaned_code_path": "generated_code/optimized/runtime/minimal/cpp/0.cpp",
                    "signature_valid": True,
                    "model_name": "gpt-5.4",
                    "from_cache": True,
                },
            )

            _, summary_path = write_aggregated_results(config, tasks)
            with summary_path.open("r", encoding="utf-8", newline="") as handle:
                rows = list(csv.DictReader(handle))

            self.assertEqual(rows[0]["runtime_improvement_ratio"], "")
            self.assertEqual(rows[0]["memory_improvement_ratio"], "")


if __name__ == "__main__":
    unittest.main()
