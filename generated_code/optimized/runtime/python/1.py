from typing import List


def separate_paren_groups(paren_string: str) -> List[str]:
    s = ''.join(c for c in paren_string if c == '(' or c == ')')
    result = []
    depth = 0
    start = 0

    for i, c in enumerate(s):
        if c == '(':
            depth += 1
        else:
            depth -= 1
            if depth == 0:
                result.append(s[start:i + 1])
                start = i + 1

    return result
