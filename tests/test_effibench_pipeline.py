from __future__ import annotations

import csv
import json
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.artifact_paths import evaluation_path, generation_metadata_path
from humaneval_pipeline.config import ExperimentConfig, PathsConfig
from humaneval_pipeline.effibench_pipeline import (
    build_effibench_prompt,
    load_effibench_tasks,
    write_effibench_aggregated_results,
)
from humaneval_pipeline.utils import write_json


class EffiBenchPipelineTests(unittest.TestCase):
    def test_load_effibench_tasks_reads_json_dataset_and_infers_entry_point(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            dataset_path = root / "dataset.json"
            dataset_path.write_text(
                json.dumps(
                    [
                        {
                            "problem_idx": 3,
                            "task_name": "Demo Task",
                            "description": "desc",
                            "markdown_description": "markdown desc",
                            "canonical_solution": (
                                "class Solution:\n"
                                "    def solve(self, x: int) -> int:\n"
                                "        return x + 1\n"
                            ),
                            "small_test_cases": "solution = Solution()\nassert solution.solve(1) == 2\n",
                            "test_case": "solution = Solution()\nassert solution.solve(2) == 3\n",
                        }
                    ]
                ),
                encoding="utf-8",
            )
            config = ExperimentConfig(
                dataset_path=str(dataset_path),
                language="python",
                project_root=root,
            )

            tasks = load_effibench_tasks(config)

            self.assertEqual(len(tasks), 1)
            self.assertEqual(tasks[0].task_id, "3")
            self.assertEqual(tasks[0].entry_point, "solve")

    def test_build_prompt_includes_description_and_tests(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            dataset_path = _write_dataset(root)
            task = load_effibench_tasks(
                ExperimentConfig(
                    dataset_path=str(dataset_path),
                    language="python",
                    project_root=root,
                )
            )[0]

            prompt = build_effibench_prompt(task, "runtime", "detailed")

            self.assertIn("Optimize for runtime", prompt)
            self.assertIn("# Task description", prompt)
            self.assertIn("# Test cases", prompt)
            self.assertIn("solution.solve", prompt)

    def test_aggregate_results_includes_memory_area_ratio(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            dataset_path = _write_dataset(root)
            config = ExperimentConfig(
                dataset_path=str(dataset_path),
                language="python",
                objectives=["runtime"],
                prompt_detail_levels=["minimal"],
                paths=_effibench_paths(),
                project_root=root,
            )
            config.ensure_directories()
            task = load_effibench_tasks(config)[0]

            before_payload = {
                "task_id": "3",
                "task_name": "Demo Task",
                "language": "python",
                "variant": "before",
                "objective": None,
                "prompt_detail": None,
                "source_path": str(root / "generated_code" / "effibench" / "baseline" / "python" / "3.py"),
                "correctness_pass": True,
                "compile_error": False,
                "test_error": False,
                "timeout": False,
                "runtime_mean_ms": 10.0,
                "runtime_std_ms": 0.0,
                "runtime_cv": 0.0,
                "memory_mean": 20.0,
                "memory_std": 0.0,
                "memory_cv": 0.0,
                "memory_area_mean": 30.0,
                "samples": [],
            }
            after_payload = {
                **before_payload,
                "variant": "after",
                "objective": "runtime",
                "prompt_detail": "minimal",
                "source_path": str(
                    root / "generated_code" / "effibench" / "optimized" / "runtime" / "minimal" / "python" / "3.py"
                ),
                "runtime_mean_ms": 5.0,
                "memory_mean": 10.0,
                "memory_area_mean": 15.0,
                "official_results_json_path": "results/effibench/official_inputs/runtime/minimal/model.json",
                "official_summary_json_path": "results/effibench/official_summaries/runtime/minimal/model.json",
            }
            write_json(evaluation_path(config, "baseline", "3", "python"), before_payload)
            write_json(
                evaluation_path(config, "optimized", "3", "python", "runtime", "minimal"),
                after_payload,
            )
            write_json(
                generation_metadata_path(config, "3", "python", "runtime", "minimal"),
                {
                    "task_id": "3",
                    "task_name": "Demo Task",
                    "language": "python",
                    "objective": "runtime",
                    "prompt_detail": "minimal",
                    "prompt_path": "prompts/effibench/runtime/minimal/python/3.txt",
                    "raw_text_path": "results/effibench/raw_responses/runtime/minimal/python/3.txt",
                    "raw_json_path": "results/effibench/raw_responses/runtime/minimal/python/3.json",
                    "cleaned_code_path": "generated_code/effibench/optimized/runtime/minimal/python/3.py",
                    "signature_valid": True,
                    "model_name": "gpt-5.4",
                    "from_cache": True,
                },
            )

            _, summary_path = write_effibench_aggregated_results(config, [task])
            with summary_path.open("r", encoding="utf-8", newline="") as handle:
                rows = list(csv.DictReader(handle))

            self.assertEqual(rows[0]["runtime_improvement_ratio"], "2.0")
            self.assertEqual(rows[0]["memory_improvement_ratio"], "2.0")
            self.assertEqual(rows[0]["memory_area_improvement_ratio"], "2.0")


def _write_dataset(root: Path) -> Path:
    dataset_path = root / "dataset.json"
    dataset_path.write_text(
        json.dumps(
            [
                {
                    "problem_idx": 3,
                    "task_name": "Demo Task",
                    "description": "desc",
                    "markdown_description": "markdown desc",
                    "canonical_solution": (
                        "class Solution:\n"
                        "    def solve(self, x: int) -> int:\n"
                        "        return x + 1\n"
                    ),
                    "small_test_cases": "solution = Solution()\nassert solution.solve(1) == 2\n",
                    "test_case": "solution = Solution()\nassert solution.solve(2) == 3\n",
                }
            ]
        ),
        encoding="utf-8",
    )
    return dataset_path


def _effibench_paths() -> PathsConfig:
    return PathsConfig(
        results_dir="results/effibench",
        analysis_dir="results/effibench/analysis",
        prompts_dir="prompts/effibench",
        generated_code_dir="generated_code/effibench",
        logs_dir="logs",
        raw_responses_dir="results/effibench/raw_responses",
        generation_metadata_dir="results/effibench/generation_metadata",
        evaluation_dir="results/effibench/evaluations",
        baseline_code_dir="generated_code/effibench/baseline",
        optimized_code_dir="generated_code/effibench/optimized",
        selected_tasks_manifest="results/effibench/selected_tasks.json",
        run_manifest="results/effibench/run_manifest.json",
        raw_runs_csv="results/effibench/raw_runs.csv",
        summary_csv="results/effibench/analysis_ready.csv",
    )


if __name__ == "__main__":
    unittest.main()
