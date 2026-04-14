from __future__ import annotations

from .models import ObjectiveMode, PromptDetailLevel

PROMPT_TEMPLATES: dict[PromptDetailLevel, dict[ObjectiveMode, str]] = {
    "minimal": {
        "runtime": (
            "Optimize the following {language} code for runtime while preserving correctness. "
            "Do not change the function signature. Output only the final optimized code."
        ),
        "memory": (
            "Optimize the following {language} code for memory usage while preserving correctness. "
            "Do not change the function signature. Output only the final optimized code."
        ),
        "balanced": (
            "Optimize the following {language} code for both runtime and memory usage while preserving "
            "correctness. Balance the tradeoff between them. Do not change the function signature. "
            "Output only the final optimized code."
        ),
    },
    "detailed": {
        "runtime": (
            "Optimize the following {language} code for runtime while preserving correctness. Do not "
            "change the function signature. Focus on reducing repeated computation, eliminating "
            "unnecessary work, improving loop efficiency, and choosing faster logic when possible. "
            "Output only the final optimized code."
        ),
        "memory": (
            "Optimize the following {language} code for memory usage while preserving correctness. Do "
            "not change the function signature. Focus on reducing unnecessary allocations, avoiding "
            "extra containers or copies, reusing storage when possible, and simplifying data usage. "
            "Output only the final optimized code."
        ),
        "balanced": (
            "Optimize the following {language} code for both runtime and memory usage while preserving "
            "correctness. Do not change the function signature. Balance the tradeoff between speed and "
            "memory use. Reduce repeated computation, avoid unnecessary allocations, and avoid making "
            "one metric much worse just to improve the other. Output only the final optimized code."
        ),
    },
}

LANGUAGE_DISPLAY_NAMES = {
    "python": "Python",
    "cpp": "C++",
    "java": "Java",
}


def build_prompt(
    language: str,
    objective: ObjectiveMode,
    prompt_detail: PromptDetailLevel,
    baseline_source: str,
) -> str:
    language_name = LANGUAGE_DISPLAY_NAMES.get(language, language)
    instruction = PROMPT_TEMPLATES[prompt_detail][objective].format(language=language_name)
    return f"{instruction}\n\nCode:\n{baseline_source.rstrip()}\n"
