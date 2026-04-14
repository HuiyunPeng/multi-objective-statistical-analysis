from __future__ import annotations

import json
import logging
import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.config import ExperimentConfig
from humaneval_pipeline.dataset_loader import BenchmarkDatasetLoader


class DatasetLoaderTests(unittest.TestCase):
    def test_loads_all_tasks_when_selected_ids_empty(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            self._write_dataset(
                root / "benchmark.json",
                [
                    self._task_row("0", "cpp stress 0", "generic stress 0"),
                    self._task_row("1", "cpp stress 1", "generic stress 1"),
                ],
            )
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                selected_task_ids=[],
                project_root=root,
            )
            loader = BenchmarkDatasetLoader(config, logging.getLogger("dataset-loader"))
            tasks = loader.load_tasks()

            self.assertEqual([task.task_id for task in tasks], ["0", "1"])
            self.assertEqual(tasks[0].performance_test_code, "cpp stress 0")
            self.assertEqual(tasks[1].performance_test_code, "cpp stress 1")

    def test_filters_selected_task_ids(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            self._write_dataset(
                root / "benchmark.json",
                [
                    self._task_row("0", "cpp stress 0", "generic stress 0"),
                    self._task_row("1", "cpp stress 1", "generic stress 1"),
                ],
            )
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                selected_task_ids=["1"],
                project_root=root,
            )
            loader = BenchmarkDatasetLoader(config, logging.getLogger("dataset-loader"))
            tasks = loader.load_tasks()

            self.assertEqual([task.task_id for task in tasks], ["1"])

    def test_limits_to_first_n_tasks_when_max_tasks_is_set(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            self._write_dataset(
                root / "benchmark.json",
                [
                    self._task_row("2", "cpp stress 2", "generic stress 2"),
                    self._task_row("0", "cpp stress 0", "generic stress 0"),
                    self._task_row("1", "cpp stress 1", "generic stress 1"),
                ],
            )
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                max_tasks=2,
                project_root=root,
            )
            loader = BenchmarkDatasetLoader(config, logging.getLogger("dataset-loader"))
            tasks = loader.load_tasks()

            self.assertEqual([task.task_id for task in tasks], ["0", "1"])

    def test_selected_task_ids_take_precedence_over_max_tasks(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            self._write_dataset(
                root / "benchmark.json",
                [
                    self._task_row("0", "cpp stress 0", "generic stress 0"),
                    self._task_row("1", "cpp stress 1", "generic stress 1"),
                    self._task_row("2", "cpp stress 2", "generic stress 2"),
                ],
            )
            config = ExperimentConfig(
                dataset_path="benchmark.json",
                language="cpp",
                selected_task_ids=["2"],
                max_tasks=1,
                project_root=root,
            )
            loader = BenchmarkDatasetLoader(config, logging.getLogger("dataset-loader"))
            tasks = loader.load_tasks()

            self.assertEqual([task.task_id for task in tasks], ["2"])

    def test_missing_required_field_raises_key_error(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            self._write_dataset(
                root / "benchmark.json",
                [
                    {
                        "task_id": "0",
                        "entry_point": "solve",
                        "function_code": "int solve(int x) { return x; }\n",
                        "cpp_stress_test": "int main() { return 0; }\n",
                    }
                ],
            )
            config = ExperimentConfig(dataset_path="benchmark.json", language="cpp", project_root=root)
            loader = BenchmarkDatasetLoader(config, logging.getLogger("dataset-loader"))

            with self.assertRaises(KeyError):
                loader.load_tasks()

    @staticmethod
    def _write_dataset(path: Path, rows: list[dict[str, str]]) -> None:
        path.write_text(json.dumps(rows), encoding="utf-8")

    @staticmethod
    def _task_row(task_id: str, cpp_stress_test: str, stress_test: str) -> dict[str, str]:
        return {
            "task_id": task_id,
            "entry_point": "solve",
            "function_code": "int solve(int x) { return x + 1; }\n",
            "test_code": "int main() { return solve(1) == 2 ? 0 : 1; }\n",
            "cpp_stress_test": cpp_stress_test,
            "stress_test": stress_test,
        }


if __name__ == "__main__":
    unittest.main()
