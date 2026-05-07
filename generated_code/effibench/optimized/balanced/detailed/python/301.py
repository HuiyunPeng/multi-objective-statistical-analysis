from typing import List


class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        res: List[str] = []

        def dfs(cur: str, last_i: int, last_j: int, open_p: str, close_p: str) -> None:
            balance = 0
            for i in range(last_i, len(cur)):
                ch = cur[i]
                if ch == open_p:
                    balance += 1
                elif ch == close_p:
                    balance -= 1

                if balance >= 0:
                    continue

                for j in range(last_j, i + 1):
                    if cur[j] == close_p and (j == last_j or cur[j - 1] != close_p):
                        dfs(cur[:j] + cur[j + 1 :], i, j, open_p, close_p)
                return

            reversed_cur = cur[::-1]
            if open_p == '(':
                dfs(reversed_cur, 0, 0, ')', '(')
            else:
                res.append(reversed_cur)

        dfs(s, 0, 0, '(', ')')
        return res
