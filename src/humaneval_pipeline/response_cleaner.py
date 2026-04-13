from __future__ import annotations

import re

from .models import CleanedCodeResult

CODE_BLOCK_PATTERN = re.compile(r"```([\w#+-]*)\n(.*?)```", re.DOTALL)

LANGUAGE_FENCE_ALIASES = {
    "python": {"python", "py"},
    "cpp": {"cpp", "c++", "cc", "cxx"},
    "java": {"java"},
}


def clean_model_response(raw_text: str, declaration: str, language: str) -> CleanedCodeResult:
    notes: list[str] = []
    cleaned = _extract_code_block(raw_text, language, notes)
    signature_valid = _validate_signature(cleaned, declaration, language, notes)
    if not signature_valid:
        notes.append("Expected declaration was not found in cleaned code.")
    return CleanedCodeResult(cleaned_code=cleaned.strip() + "\n", signature_valid=signature_valid, notes=notes)


def _extract_code_block(raw_text: str, language: str, notes: list[str]) -> str:
    blocks = list(CODE_BLOCK_PATTERN.finditer(raw_text))
    if not blocks:
        notes.append("No markdown code fence found; using raw response text.")
        return raw_text.strip()

    aliases = LANGUAGE_FENCE_ALIASES.get(language, {language})
    preferred_block = None
    for block in blocks:
        label = block.group(1).strip().lower()
        if label in aliases:
            preferred_block = block
            notes.append(f"Selected fenced code block tagged as {label}.")
            break

    if preferred_block is None:
        preferred_block = max(blocks, key=lambda block: len(block.group(2)))
        notes.append("Selected the longest fenced code block.")

    return preferred_block.group(2).strip()


def _validate_signature(code: str, declaration: str, language: str, notes: list[str]) -> bool:
    expected_signature = _extract_expected_signature(declaration, language)
    if expected_signature is None:
        notes.append("Could not isolate callable signature; falling back to full declaration match.")
        expected_signature = declaration
    else:
        notes.append(f"Validating callable signature: {expected_signature}")

    normalized_code = _normalize_for_signature_match(code)
    normalized_signature = _normalize_for_signature_match(expected_signature)
    return normalized_signature in normalized_code


def _extract_expected_signature(declaration: str, language: str) -> str | None:
    non_empty_lines = [line.rstrip() for line in declaration.splitlines() if line.strip()]
    if not non_empty_lines:
        return None

    if language == "python":
        for line in non_empty_lines:
            stripped = line.strip()
            if stripped.startswith("def "):
                return stripped
        return None

    if language == "java":
        for line in non_empty_lines:
            stripped = line.strip()
            if "(" in stripped and stripped.endswith("{") and not stripped.startswith("class "):
                return stripped
        return None

    if language == "cpp":
        for line in reversed(non_empty_lines):
            stripped = line.strip()
            if "(" in stripped and stripped.endswith("{"):
                return stripped
        return None

    return non_empty_lines[-1].strip()


def _normalize_for_signature_match(text: str) -> str:
    normalized = re.sub(r"\s+", "", text)
    normalized = normalized.replace("std::", "")
    return normalized
