from __future__ import annotations

import ast
import re

from .models import CleanedCodeResult

CODE_BLOCK_PATTERN = re.compile(r"```([\w#+-]*)\n(.*?)```", re.DOTALL)

LANGUAGE_FENCE_ALIASES = {
    "python": {"python", "py"},
    "cpp": {"cpp", "c++", "cc", "cxx"},
    "java": {"java"},
}


def clean_model_response(
    raw_text: str,
    function_code: str,
    entry_point: str,
    language: str,
) -> CleanedCodeResult:
    notes: list[str] = []
    cleaned = _extract_code_block(raw_text, language, notes)
    signature_valid = _validate_signature(cleaned, function_code, entry_point, language, notes)
    if not signature_valid:
        notes.append("Expected callable signature was not found in cleaned code.")
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


def _validate_signature(
    code: str,
    function_code: str,
    entry_point: str,
    language: str,
    notes: list[str],
) -> bool:
    if language == "cpp":
        return _validate_cpp_signature(code, function_code, entry_point, notes)
    if language == "python":
        return _validate_python_signature(code, function_code, entry_point, notes)

    expected_signature = _extract_signature(function_code, entry_point, language)
    actual_signature = _extract_signature(code, entry_point, language)
    if expected_signature and actual_signature:
        notes.append(f"Validating callable signature: {expected_signature}")
        return _normalize_signature(expected_signature) == _normalize_signature(actual_signature)

    notes.append("Falling back to entry-point presence validation.")
    return f"{entry_point}(" in code


def _validate_python_signature(
    code: str,
    function_code: str,
    entry_point: str,
    notes: list[str],
) -> bool:
    expected_signature = _extract_signature(function_code, entry_point, "python")
    actual_signature = _extract_signature(code, entry_point, "python")
    if expected_signature and actual_signature:
        notes.append(f"Validating callable signature: {expected_signature}")

    expected_shape = _extract_python_callable_shape(function_code, entry_point)
    actual_shape = _extract_python_callable_shape(code, entry_point)
    if expected_shape and actual_shape:
        return expected_shape == actual_shape

    if expected_signature and actual_signature:
        return _normalize_signature(expected_signature) == _normalize_signature(actual_signature)

    notes.append("Falling back to entry-point presence validation.")
    return f"{entry_point}(" in code


def _validate_cpp_signature(
    code: str,
    function_code: str,
    entry_point: str,
    notes: list[str],
) -> bool:
    expected_signature = _extract_signature(function_code, entry_point, "cpp")
    actual_signature = _extract_signature(code, entry_point, "cpp")
    if expected_signature and actual_signature:
        notes.append(f"Validating callable signature: {expected_signature}")
        return _normalize_cpp_signature(expected_signature) == _normalize_cpp_signature(actual_signature)

    notes.append("Could not isolate a full C++ signature; falling back to entry-point presence.")
    return f"{entry_point}(" in code


def _extract_signature(source: str, entry_point: str, language: str) -> str | None:
    if language == "python":
        for line in source.splitlines():
            stripped = line.strip()
            if stripped.startswith(f"def {entry_point}("):
                return stripped
        return None

    lines = source.splitlines()
    for index, line in enumerate(lines):
        stripped = line.strip()
        if f"{entry_point}(" not in stripped:
            continue
        if language == "java" and stripped.startswith("class "):
            continue
        collected = [stripped]
        if _signature_complete(stripped, language):
            return stripped
        for next_line in lines[index + 1 :]:
            next_stripped = next_line.strip()
            if not next_stripped:
                continue
            collected.append(next_stripped)
            candidate = " ".join(collected)
            if _signature_complete(candidate, language):
                return candidate
        break
    return None


def _signature_complete(signature: str, language: str) -> bool:
    if language == "python":
        return signature.endswith(":")
    return "{" in signature or signature.endswith(";")


def _extract_python_callable_shape(source: str, entry_point: str) -> tuple[str, ...] | None:
    try:
        module = ast.parse(source)
    except SyntaxError:
        return None

    solution_method = _find_python_solution_method(module, entry_point)
    if solution_method is not None:
        return _python_callable_shape(solution_method)

    for node in ast.walk(module):
        if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)) and node.name == entry_point:
            return _python_callable_shape(node)
    return None


def _find_python_solution_method(
    module: ast.Module,
    entry_point: str,
) -> ast.FunctionDef | ast.AsyncFunctionDef | None:
    for node in module.body:
        if not isinstance(node, ast.ClassDef) or node.name != "Solution":
            continue
        for member in node.body:
            if isinstance(member, (ast.FunctionDef, ast.AsyncFunctionDef)) and member.name == entry_point:
                return member
    return None


def _python_callable_shape(node: ast.FunctionDef | ast.AsyncFunctionDef) -> tuple[str, ...]:
    params = [argument.arg for argument in node.args.posonlyargs]
    params.extend(argument.arg for argument in node.args.args)
    if node.args.vararg is not None:
        params.append(f"*{node.args.vararg.arg}")
    params.extend(argument.arg for argument in node.args.kwonlyargs)
    if node.args.kwarg is not None:
        params.append(f"**{node.args.kwarg.arg}")
    return tuple(params)


def _normalize_signature(text: str) -> str:
    normalized = re.sub(r"\s+", "", text)
    return normalized.replace("std::", "")


def _normalize_cpp_signature(text: str) -> str:
    match = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\((.*)\)", text)
    if not match:
        return _normalize_signature(text)
    name = match.group(1)
    params = match.group(2)
    return _normalize_signature(f"{name}({params})")
