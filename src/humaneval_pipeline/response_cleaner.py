from __future__ import annotations

import re

from .models import CleanedCodeResult
from .utils import collapse_whitespace

CODE_BLOCK_PATTERN = re.compile(r"```([\w#+-]*)\n(.*?)```", re.DOTALL)

LANGUAGE_FENCE_ALIASES = {
    "python": {"python", "py"},
    "cpp": {"cpp", "c++", "cc", "cxx"},
    "java": {"java"},
}


def clean_model_response(raw_text: str, declaration: str, language: str) -> CleanedCodeResult:
    notes: list[str] = []
    cleaned = _extract_code_block(raw_text, language, notes)
    signature_valid = _validate_signature(cleaned, declaration)
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


def _validate_signature(code: str, declaration: str) -> bool:
    normalized_code = collapse_whitespace(code)
    normalized_declaration = collapse_whitespace(declaration)
    return normalized_declaration in normalized_code
