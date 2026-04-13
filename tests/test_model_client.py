from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.config import (
    BenchmarkConfig,
    DatasetConfig,
    ExecutionConfig,
    ExperimentConfig,
    ModelConfig,
    PathsConfig,
)
from humaneval_pipeline.model_client import OpenAIModelClient


class ModelClientTests(unittest.TestCase):
    def test_cache_key_is_deterministic(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = ExperimentConfig(
                dataset=DatasetConfig(source_urls=["https://example.com/{language}.jsonl"]),
                model=ModelConfig(cache_dir="cache/model"),
                benchmark=BenchmarkConfig(),
                execution=ExecutionConfig(),
                paths=PathsConfig(),
                project_root=Path(tmpdir),
            )
            config.ensure_directories()
            client = OpenAIModelClient(config)
            payload = client._build_request_payload("optimize this code")
            self.assertEqual(client._build_cache_key(payload), client._build_cache_key(payload))

    def test_load_api_key_from_dotenv(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            (root / ".env").write_text("OPENAI_API_KEY=test-from-dotenv\n", encoding="utf-8")
            config = ExperimentConfig(
                dataset=DatasetConfig(source_urls=["https://example.com/{language}.jsonl"]),
                model=ModelConfig(cache_dir="cache/model"),
                benchmark=BenchmarkConfig(),
                execution=ExecutionConfig(),
                paths=PathsConfig(),
                project_root=root,
            )
            config.ensure_directories()
            client = OpenAIModelClient(config)
            self.assertEqual(client._load_api_key(), "test-from-dotenv")

    def test_gpt5_request_omits_temperature(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = ExperimentConfig(
                dataset=DatasetConfig(source_urls=["https://example.com/{language}.jsonl"]),
                model=ModelConfig(name="gpt-5.4", temperature=0, cache_dir="cache/model"),
                benchmark=BenchmarkConfig(),
                execution=ExecutionConfig(),
                paths=PathsConfig(),
                project_root=Path(tmpdir),
            )
            config.ensure_directories()
            client = OpenAIModelClient(config)
            payload = client._build_request_payload("optimize this code")
            self.assertNotIn("temperature", payload)

    def test_non_gpt5_request_keeps_temperature(self) -> None:
        with tempfile.TemporaryDirectory() as tmpdir:
            config = ExperimentConfig(
                dataset=DatasetConfig(source_urls=["https://example.com/{language}.jsonl"]),
                model=ModelConfig(name="gpt-4.1", temperature=0, cache_dir="cache/model"),
                benchmark=BenchmarkConfig(),
                execution=ExecutionConfig(),
                paths=PathsConfig(),
                project_root=Path(tmpdir),
            )
            config.ensure_directories()
            client = OpenAIModelClient(config)
            payload = client._build_request_payload("optimize this code")
            self.assertEqual(payload["temperature"], 0)


if __name__ == "__main__":
    unittest.main()
