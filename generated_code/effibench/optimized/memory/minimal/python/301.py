from typing import List

class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        result: List[str] = []

        def remove(cur: str, scan_start: int, remove_start: int, open_p: str, close_p: str) -> None:
            balance = 0

            for i in range(scan_start, len(cur)):
                ch = cur[i]
                if ch == open_p:
                    balance += 1
                elif ch == close_p:
                    balance -= 1

                if balance >= 0:
                    continue

                # Too many close_p found; try removing one of them.
                for j in range(remove_start, i + 1):
                    if cur[j] == close_p and (j == remove_start or cur[j - 1] != close_p):
                        remove(cur[:j] + cur[j + 1:], i, j, open_p, close_p)
                return

            # No extra close_p. Reverse and remove extra open_p in the same way.
            reversed_cur = cur[::-1]
            if open_p == '(':
                remove(reversed_cur, 0, 0, ')', '(')
            else:
                result.append(reversed_cur)

        remove(s, 0, 0, '(', ')')
        return result
