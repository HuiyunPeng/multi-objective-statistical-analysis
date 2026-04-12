from __future__ import annotations

import gzip
import json
import logging
from pathlib import Path
from typing import Any

import requests

from .config import ExperimentConfig
from .models import Language, TaskRecord
from .utils import ensure_parent, write_json


class HumanEvalXLoader:
    REQUIRED_FIELDS = (
        "task_id",
        "prompt",
        "declaration",
        "canonical_solution",
        "test",
        "example_test",
    )

    def __init__(self, config: ExperimentConfig, logger: logging.Logger) -> None:
        self.config = config
        self.logger = logger

    def load_aligned_tasks(self) -> dict[str, dict[str, TaskRecord]]:
        by_language = {
            language: self._load_language(language) for language in self.config.dataset.languages
        }
        common_problem_ids = set.intersection(
            *(set(records.keys()) for records in by_language.values())
        )
        if not common_problem_ids:
            raise RuntimeError("No common HumanEval-X problem IDs were found across languages.")

        selected_problem_ids = self._select_problem_ids(common_problem_ids)
        aligned: dict[str, dict[str, TaskRecord]] = {}
        for language, records in by_language.items():
            aligned[language] = {
                problem_id: records[problem_id] for problem_id in selected_problem_ids
            }
        return aligned

    def save_selected_manifest(self, aligned_tasks: dict[str, dict[str, TaskRecord]]) -> None:
        payload: dict[str, Any] = {
            "languages": self.config.dataset.languages,
            "selected_problem_ids": list(next(iter(aligned_tasks.values())).keys()),
            "tasks": {
                language: [task.to_dict() for task in tasks.values()]
                for language, tasks in aligned_tasks.items()
            },
        }
        write_json(self.config.resolve_path(self.config.paths.selected_tasks_manifest), payload)

    def _load_language(self, language: str) -> dict[str, TaskRecord]:
        path = self._ensure_dataset_file(language)
        rows = self._read_jsonl(path)
        records: dict[str, TaskRecord] = {}
        for row in rows:
            missing_fields = [field for field in self.REQUIRED_FIELDS if field not in row]
            if missing_fields:
                raise KeyError(
                    f"Dataset row for {language} is missing fields {missing_fields}. "
                    f"Available fields: {sorted(row.keys())}"
                )

            task_id = str(row["task_id"])
            problem_id = self.normalize_problem_id(task_id)
            records[problem_id] = TaskRecord(
                problem_id=problem_id,
                task_id=task_id,
                language=language,  # type: ignore[arg-type]
                prompt=str(row["prompt"]),
                declaration=str(row["declaration"]),
                canonical_solution=str(row["canonical_solution"]),
                test=str(row["test"]),
                example_test=str(row["example_test"]),
            )
        self.logger.info("Loaded %s HumanEval-X tasks for %s", len(records), language)
        return records

    def _ensure_dataset_file(self, language: str) -> Path:
        local_file = self.config.dataset.local_files.get(language)
        if local_file:
            local_path = self.config.resolve_path(local_file)
            if not local_path.exists():
                raise FileNotFoundError(f"Configured local dataset file does not exist: {local_path}")
            return local_path

        cache_path = self.config.resolve_path(self.config.dataset.cache_dir) / f"{language}.jsonl"
        if cache_path.exists():
            return cache_path

        last_error: Exception | None = None
        for url_template in self.config.dataset.source_urls:
            url = url_template.format(language=language)
            try:
                self.logger.info("Downloading HumanEval-X %s from %s", language, url)
                response = requests.get(url, timeout=60)
                response.raise_for_status()
                content = response.content
                if content[:2] == b"\x1f\x8b":
                    text = gzip.decompress(content).decode("utf-8")
                else:
                    text = response.text
                ensure_parent(cache_path)
                cache_path.write_text(text, encoding="utf-8")
                return cache_path
            except Exception as exc:  # noqa: BLE001
                last_error = exc
                self.logger.warning("Failed to download %s from %s: %s", language, url, exc)

        raise RuntimeError(f"Unable to download HumanEval-X data for {language}") from last_error

    @staticmethod
    def normalize_problem_id(task_id: str) -> str:
        if "/" in task_id:
            return task_id.split("/", 1)[1]
        return task_id

    def _select_problem_ids(self, common_problem_ids: set[str]) -> list[str]:
        if self.config.dataset.selected_problem_ids:
            selected = [str(problem_id) for problem_id in self.config.dataset.selected_problem_ids]
            missing = sorted(set(selected) - common_problem_ids)
            if missing:
                raise ValueError(
                    "Selected problem IDs are not present in all configured languages: "
                    + ", ".join(missing)
                )
            return selected

        sorted_ids = sorted(common_problem_ids, key=self._sort_key)
        return sorted_ids[: self.config.dataset.pilot_size]

    @staticmethod
    def _sort_key(problem_id: str) -> tuple[int, str]:
        if problem_id.isdigit():
            return (0, f"{int(problem_id):08d}")
        return (1, problem_id)

    @staticmethod
    def _read_jsonl(path: Path) -> list[dict[str, Any]]:
        rows: list[dict[str, Any]] = []
        with path.open("r", encoding="utf-8") as handle:
            for line in handle:
                line = line.strip()
                if not line:
                    continue
                rows.append(json.loads(line))
        return rows
