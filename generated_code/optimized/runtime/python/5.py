from typing import List


def intersperse(numbers: List[int], delimeter: int) -> List[int]:
    if not numbers:
        return []
    result = [delimeter] * (len(numbers) * 2 - 1)
    result[::2] = numbers
    return result
