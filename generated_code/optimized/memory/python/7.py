from typing import List


def filter_by_substring(strings: List[str], substring: str) -> List[str]:
    """ Filter an input list of strings only for ones that contain given substring
    >>> filter_by_substring([], 'a')
    []
    >>> filter_by_substring(['abc', 'bacd', 'cde', 'array'], 'a')
    ['abc', 'bacd', 'array']
    """
    write = 0
    for read in range(len(strings)):
        s = strings[read]
        if substring in s:
            strings[write] = s
            write += 1
    del strings[write:]
    return strings
