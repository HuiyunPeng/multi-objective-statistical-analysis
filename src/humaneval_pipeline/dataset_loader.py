from __future__ import annotations

import json
import logging
from pathlib import Path
from typing import Any

from .config import ExperimentConfig
from .models import TaskRecord
from .utils import write_json


class BenchmarkDatasetLoader:
    REQUIRED_FIELDS = ("task_id", "entry_point", "function_code", "test_code")

    def __init__(self, config: ExperimentConfig, logger: logging.Logger) -> None:
        self.config = config
        self.logger = logger

    def load_tasks(self) -> list[TaskRecord]:
        dataset_path = self.config.resolve_path(self.config.dataset_path)
        if not dataset_path.exists():
            raise FileNotFoundError(f"Dataset file does not exist: {dataset_path}")

        payload = json.loads(dataset_path.read_text(encoding="utf-8"))
        if not isinstance(payload, list):
            raise ValueError("Dataset file must contain a JSON array of task objects.")

        all_tasks = [self._build_task_record(row) for row in payload]
        selected = self._select_tasks(all_tasks)
        self.logger.info(
            "Loaded %s %s benchmark tasks from %s",
            len(selected),
            self.config.language,
            dataset_path,
        )
        return selected

    def save_selected_manifest(self, tasks: list[TaskRecord]) -> None:
        payload: dict[str, Any] = {
            "language": self.config.language,
            "dataset_path": self.config.dataset_path,
            "selected_task_ids": [task.task_id for task in tasks],
            "max_tasks": self.config.max_tasks,
            "tasks": [task.to_dict() for task in tasks],
        }
        write_json(self.config.resolve_path(self.config.paths.selected_tasks_manifest), payload)

    def _build_task_record(self, row: Any) -> TaskRecord:
        if not isinstance(row, dict):
            raise ValueError(f"Dataset row must be an object, got {type(row).__name__}.")

        missing_fields = [field for field in self.REQUIRED_FIELDS if field not in row]
        if missing_fields:
            raise KeyError(
                f"Dataset row is missing fields {missing_fields}. "
                f"Available fields: {sorted(row.keys())}"
            )

        performance_test_code = self._resolve_performance_test_code(row)
        return TaskRecord(
            task_id=str(row["task_id"]),
            language=self.config.language,  # type: ignore[arg-type]
            entry_point=str(row["entry_point"]),
            function_code=str(row["function_code"]),
            test_code=str(row["test_code"]),
            stress_test=self._maybe_string(row.get("stress_test")),
            cpp_stress_test=self._maybe_string(row.get("cpp_stress_test")),
            performance_test_code=performance_test_code,
        )

    def _resolve_performance_test_code(self, row: dict[str, Any]) -> str:
        if self.config.language == "cpp":
            cpp_stress_test = self._maybe_string(row.get("cpp_stress_test"))
            if cpp_stress_test:
                return cpp_stress_test

        generic_stress_test = self._maybe_string(row.get("stress_test"))
        if generic_stress_test:
            return generic_stress_test

        task_id = row.get("task_id", "<unknown>")
        raise KeyError(f"Task {task_id} is missing a usable performance stress test field.")

    def _select_tasks(self, tasks: list[TaskRecord]) -> list[TaskRecord]:
        sorted_tasks = sorted(tasks, key=lambda task: self._sort_key(task.task_id))

        if not self.config.selected_task_ids:
            if self.config.max_tasks is None:
                return sorted_tasks
            return sorted_tasks[: self.config.max_tasks]

        selected_ids = {str(task_id) for task_id in self.config.selected_task_ids}
        filtered = [task for task in sorted_tasks if task.task_id in selected_ids]
        missing_ids = sorted(selected_ids - {task.task_id for task in filtered}, key=self._sort_key)
        if missing_ids:
            raise ValueError(f"Selected task IDs not found in dataset: {missing_ids}")
        return filtered

    @staticmethod
    def _sort_key(task_id: str) -> tuple[int, str]:
        if task_id.isdigit():
            return (0, f"{int(task_id):08d}")
        return (1, task_id)

    @staticmethod
    def _maybe_string(value: Any) -> str | None:
        if value is None:
            return None
        return str(value)
