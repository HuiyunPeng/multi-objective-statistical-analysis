from __future__ import annotations

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
from humaneval_pipeline.config import (
    BenchmarkConfig,
    DatasetConfig,
    ExecutionConfig,
    ExperimentConfig,
    ModelConfig,
    PathsConfig,
)
from humaneval_pipeline.models import TaskRecord
from humaneval_pipeline.utils import write_json


class AggregatorTests(unittest.TestCase):
    def test_summary_includes_reused_baseline_metrics(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = ExperimentConfig(
                dataset=DatasetConfig(source_urls=["https://example.com/{language}.jsonl"]),
                model=ModelConfig(),
                benchmark=BenchmarkConfig(),
                execution=ExecutionConfig(),
                paths=PathsConfig(),
                project_root=Path(tmpdir),
            )
            config.ensure_directories()

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
            aligned_tasks = {"python": {"0": task}}

            before_payload = {
                "problem_id": "0",
                "task_id": "Python/0",
                "language": "python",
                "variant": "before",
                "objective": None,
                "source_path": str(Path(tmpdir) / "generated_code" / "baseline.py"),
                "correctness_pass": True,
                "compile_error": False,
                "test_error": False,
                "timeout": False,
                "runtime_mean": 10.0,
                "runtime_std": 1.0,
                "runtime_cv": 0.1,
                "memory_mean": 100.0,
                "memory_std": 10.0,
                "memory_cv": 0.1,
                "samples": [
                    {
                        "repetition_index": 1,
                        "runtime_seconds": 10.0,
                        "peak_memory_bytes": 100,
                        "returncode": 0,
                        "stdout": "",
                        "stderr": "",
                    }
                ],
            }
            write_json(evaluation_path(config, "baseline", "0", "python"), before_payload)

            for objective in ("runtime", "memory", "balanced"):
                after_payload = {
                    **before_payload,
                    "variant": "after",
                    "objective": objective,
                    "source_path": str(Path(tmpdir) / "generated_code" / f"{objective}.py"),
                    "runtime_mean": 5.0,
                    "memory_mean": 50.0,
                }
                write_json(
                    evaluation_path(config, "optimized", "0", "python", objective), after_payload
                )
                write_json(
                    generation_metadata_path(config, "0", "python", objective),
                    {
                        "problem_id": "0",
                        "task_id": "Python/0",
                        "language": "python",
                        "objective": objective,
                        "prompt_path": f"prompts/{objective}/python/0.txt",
                        "raw_text_path": f"results/raw_responses/{objective}/python/0.txt",
                        "raw_json_path": f"results/raw_responses/{objective}/python/0.json",
                        "cleaned_code_path": f"generated_code/optimized/{objective}/python/0.py",
                        "signature_valid": True,
                        "model_name": "gpt-5.4",
                        "from_cache": True,
                    },
                )

            _, summary_path = write_aggregated_results(config, aligned_tasks)
            summary_text = summary_path.read_text(encoding="utf-8")
            self.assertIn("runtime_improvement_ratio", summary_text)
            self.assertIn("2.0", summary_text)


if __name__ == "__main__":
    unittest.main()
