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
    def test_build_prompt_uses_prompt_detail_and_language_name(self) -> None:
        baseline_source = "int solve(int x) { return x + 1; }\n"
        prompt = build_prompt("cpp", "memory", "detailed", baseline_source)

        self.assertIn("Optimize the following C++ code for memory usage", prompt)
        self.assertIn("reducing unnecessary allocations", prompt)
        self.assertIn("Code:", prompt)

    def test_cleaner_prefers_matching_language_fence(self) -> None:
        function_code = "int solve(int x) { return x + 1; }\n"
        raw_text = "```text\nignore\n```\n```cpp\nint solve(int x) { return x + 1; }\n```"
        cleaned = clean_model_response(raw_text, function_code, "solve", "cpp")

        self.assertTrue(cleaned.signature_valid)
        self.assertEqual(cleaned.cleaned_code, "int solve(int x) { return x + 1; }\n")

    def test_python_signature_validation_ignores_annotation_differences(self) -> None:
        function_code = (
            "class Solution:\n"
            "    def solve(self, nums: List[int]) -> List[int]:\n"
            "        return nums\n"
        )
        raw_text = (
            "```python\n"
            "class Solution:\n"
            "    def solve(self, nums):\n"
            "        return nums\n"
            "```"
        )

        cleaned = clean_model_response(raw_text, function_code, "solve", "python")

        self.assertTrue(cleaned.signature_valid)
        self.assertEqual(
            cleaned.cleaned_code,
            "class Solution:\n    def solve(self, nums):\n        return nums\n",
        )

    def test_cpp_signature_validation_ignores_include_reordering(self) -> None:
        function_code = (
            "#include <vector>\n#include <algorithm>\nusing namespace std;\n"
            "bool has_close_elements(vector<float> numbers, float threshold) {\n"
            "    return false;\n}\n"
        )
        raw_text = (
            "```cpp\n#include <algorithm>\n#include <vector>\nusing namespace std;\n"
            "bool has_close_elements(vector<float> numbers, float threshold) {\n"
            "    return true;\n}\n```\n"
        )
        cleaned = clean_model_response(raw_text, function_code, "has_close_elements", "cpp")

        self.assertTrue(cleaned.signature_valid)

    def test_cleaner_rejects_wrong_entry_point(self) -> None:
        function_code = "int solve(int x) { return x + 1; }\n"
        raw_text = "```cpp\nint other(int x) { return x + 1; }\n```"
        cleaned = clean_model_response(raw_text, function_code, "solve", "cpp")

        self.assertFalse(cleaned.signature_valid)
        self.assertTrue(cleaned.notes)


if __name__ == "__main__":
    unittest.main()
