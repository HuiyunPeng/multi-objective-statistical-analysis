from __future__ import annotations

import json
import os
import time
from pathlib import Path
from typing import Any

from .config import ExperimentConfig
from .models import ModelCallResult
from .utils import read_json, sha256_text, write_json


class OpenAIModelClient:
    def __init__(self, config: ExperimentConfig) -> None:
        self.config = config
        self._client: Any | None = None

    def generate(self, prompt: str) -> ModelCallResult:
        cache_key = self._build_cache_key(prompt)
        cache_path = self._cache_path(cache_key)
        if cache_path.exists():
            cached = read_json(cache_path)
            return ModelCallResult(
                cache_key=cache_key,
                raw_text=str(cached["raw_text"]),
                response_json=dict(cached["response_json"]),
                from_cache=True,
            )

        response_json: dict[str, Any] | None = None
        raw_text = ""
        for attempt in range(1, self.config.model.retries + 1):
            try:
                response = self._client_instance().responses.create(
                    model=self.config.model.name,
                    input=prompt,
                    reasoning={"effort": self.config.model.reasoning_effort},
                    temperature=self.config.model.temperature,
                    max_output_tokens=self.config.model.max_output_tokens,
                )
                response_json = self._response_to_json(response)
                raw_text = self._extract_output_text(response, response_json)
                break
            except Exception:  # noqa: BLE001
                if attempt >= self.config.model.retries:
                    raise
                sleep_seconds = self.config.model.retry_backoff_seconds * attempt
                time.sleep(sleep_seconds)

        assert response_json is not None
        write_json(
            cache_path,
            {
                "cache_key": cache_key,
                "model": self.config.model.name,
                "reasoning_effort": self.config.model.reasoning_effort,
                "temperature": self.config.model.temperature,
                "max_output_tokens": self.config.model.max_output_tokens,
                "raw_text": raw_text,
                "response_json": response_json,
            },
        )
        return ModelCallResult(
            cache_key=cache_key,
            raw_text=raw_text,
            response_json=response_json,
            from_cache=False,
        )

    def _build_cache_key(self, prompt: str) -> str:
        serialized = json.dumps(
            {
                "model": self.config.model.name,
                "reasoning_effort": self.config.model.reasoning_effort,
                "temperature": self.config.model.temperature,
                "max_output_tokens": self.config.model.max_output_tokens,
                "prompt": prompt,
            },
            sort_keys=True,
        )
        return sha256_text(serialized)

    def _cache_path(self, cache_key: str) -> Path:
        return self.config.resolve_path(self.config.model.cache_dir) / f"{cache_key}.json"

    def _client_instance(self) -> Any:
        if self._client is None:
            api_key = self._load_api_key()
            if not api_key:
                raise RuntimeError(
                    "OPENAI_API_KEY was not found in .env or the current environment."
                )

            from openai import OpenAI  # Imported lazily for easier local testing.

            client_kwargs: dict[str, Any] = {"api_key": api_key}
            if self.config.model.base_url:
                client_kwargs["base_url"] = self.config.model.base_url
            self._client = OpenAI(**client_kwargs)
        return self._client

    def _load_api_key(self) -> str | None:
        env_path = self.config.project_root / ".env"
        if env_path.exists():
            env_values = self._parse_dotenv(env_path)
            api_key = env_values.get("OPENAI_API_KEY")
            if api_key:
                return api_key
        return os.environ.get("OPENAI_API_KEY")

    @staticmethod
    def _parse_dotenv(path: Path) -> dict[str, str]:
        values: dict[str, str] = {}
        for raw_line in path.read_text(encoding="utf-8").splitlines():
            line = raw_line.strip()
            if not line or line.startswith("#") or "=" not in line:
                continue
            key, value = line.split("=", 1)
            key = key.strip()
            value = value.strip()
            if value and value[0] == value[-1] and value[0] in {'"', "'"}:
                value = value[1:-1]
            values[key] = value
        return values

    @staticmethod
    def _response_to_json(response: Any) -> dict[str, Any]:
        if hasattr(response, "model_dump"):
            return dict(response.model_dump())
        if hasattr(response, "to_dict"):
            return dict(response.to_dict())
        if isinstance(response, dict):
            return dict(response)
        raise TypeError("Unable to serialize OpenAI response object.")

    @staticmethod
    def _extract_output_text(response: Any, response_json: dict[str, Any]) -> str:
        output_text = getattr(response, "output_text", None)
        if isinstance(output_text, str) and output_text.strip():
            return output_text

        chunks: list[str] = []
        for item in response_json.get("output", []):
            for content in item.get("content", []):
                text = content.get("text")
                if isinstance(text, str) and text.strip():
                    chunks.append(text)
        if chunks:
            return "\n".join(chunks)

        raise ValueError("OpenAI response did not contain output text.")
