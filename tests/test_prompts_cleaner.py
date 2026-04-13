from __future__ import annotations

import sys
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.prompts import build_prompt
from humaneval_pipeline.response_cleaner import clean_model_response


class PromptAndCleanerTests(unittest.TestCase):
    def test_build_prompt_is_deterministic(self) -> None:
        baseline_source = "def solve(x):\n    return x + 1\n"
        prompt_one = build_prompt("python", "runtime", baseline_source)
        prompt_two = build_prompt("python", "runtime", baseline_source)
        self.assertEqual(prompt_one, prompt_two)
        self.assertIn("Optimize the provided code for runtime", prompt_one)
        self.assertIn("Provided code:", prompt_one)

    def test_cleaner_prefers_matching_language_fence(self) -> None:
        raw_text = "```text\nignore\n```\n```python\ndef solve(x):\n    return x + 1\n```"
        cleaned = clean_model_response(raw_text, "def solve(x):", "python")
        self.assertTrue(cleaned.signature_valid)
        self.assertEqual(cleaned.cleaned_code, "def solve(x):\n    return x + 1\n")

    def test_cleaner_reports_missing_signature(self) -> None:
        raw_text = "```python\nprint('hello')\n```"
        cleaned = clean_model_response(raw_text, "def solve(x):", "python")
        self.assertFalse(cleaned.signature_valid)
        self.assertTrue(cleaned.notes)

    def test_python_signature_validation_ignores_added_imports(self) -> None:
        declaration = "from typing import List, Tuple\n\n\ndef sum_product(numbers: List[int]) -> Tuple[int, int]:\n"
        raw_text = (
            "from typing import List, Tuple\n"
            "import math\n\n\n"
            "def sum_product(numbers: List[int]) -> Tuple[int, int]:\n"
            "    return sum(numbers), math.prod(numbers)\n"
        )
        cleaned = clean_model_response(raw_text, declaration, "python")
        self.assertTrue(cleaned.signature_valid)

    def test_cpp_signature_validation_ignores_include_reordering(self) -> None:
        declaration = (
            "#include<stdio.h>\n#include<vector>\n#include<math.h>\nusing namespace std;\n"
            "#include<algorithm>\n#include<stdlib.h>\n"
            "bool has_close_elements(vector<float> numbers, float threshold){\n"
        )
        raw_text = (
            "#include <vector>\n#include <algorithm>\n#include <cmath>\nusing namespace std;\n\n"
            "bool has_close_elements(vector<float> numbers, float threshold) {\n"
            "    return false;\n}\n"
        )
        cleaned = clean_model_response(raw_text, declaration, "cpp")
        self.assertTrue(cleaned.signature_valid)

    def test_java_signature_validation_ignores_missing_extra_imports(self) -> None:
        declaration = (
            "import java.util.*;\nimport java.lang.*;\n\nclass Solution {\n"
            "    public boolean hasCloseElements(List<Double> numbers, double threshold) {\n"
        )
        raw_text = (
            "import java.util.*;\n\nclass Solution {\n"
            "    public boolean hasCloseElements(List<Double> numbers, double threshold) {\n"
            "        return false;\n    }\n}\n"
        )
        cleaned = clean_model_response(raw_text, declaration, "java")
        self.assertTrue(cleaned.signature_valid)


if __name__ == "__main__":
    unittest.main()
