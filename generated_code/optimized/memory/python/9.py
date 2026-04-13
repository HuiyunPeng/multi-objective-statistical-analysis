from typing import List


def rolling_max(numbers: List[int]) -> List[int]:
    """ From a given list of integers, generate a list of rolling maximum element found until given moment
    in the sequence.
    >>> rolling_max([1, 2, 3, 2, 3, 4, 2])
    [1, 2, 3, 3, 3, 4, 4]
    """
    n = len(numbers)
    if n == 0:
        return []

    result = [0] * n
    running_max = numbers[0]
    result[0] = running_max

    for i in range(1, n):
        x = numbers[i]
        if x > running_max:
            running_max = x
        result[i] = running_max

    return result
