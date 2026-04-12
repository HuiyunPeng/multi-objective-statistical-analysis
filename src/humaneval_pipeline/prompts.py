from __future__ import annotations

from .models import ObjectiveMode

PROMPT_TEMPLATES: dict[ObjectiveMode, str] = {
    "runtime": (
        "You are given a programming task in {language}. Optimize the provided "
        "code for runtime while preserving correctness. Do not change the "
        "function signature. Do not add explanations. Output only the final "
        "optimized code."
    ),
    "memory": (
        "You are given a programming task in {language}. Optimize the provided "
        "code for memory usage while preserving correctness. Do not change the "
        "function signature. Do not add explanations. Output only the final "
        "optimized code."
    ),
    "balanced": (
        "You are given a programming task in {language}. Optimize the provided "
        "code for both runtime and memory usage while preserving correctness. "
        "Balance the tradeoff between them. Do not change the function "
        "signature. Do not add explanations. Output only the final optimized code."
    ),
}

LANGUAGE_DISPLAY_NAMES = {
    "python": "Python",
    "cpp": "C++",
    "java": "Java",
}


def build_prompt(language: str, objective: ObjectiveMode, baseline_source: str) -> str:
    language_name = LANGUAGE_DISPLAY_NAMES.get(language, language)
    instruction = PROMPT_TEMPLATES[objective].format(language=language_name)
    return f"{instruction}\n\nProvided code:\n{baseline_source.rstrip()}\n"
