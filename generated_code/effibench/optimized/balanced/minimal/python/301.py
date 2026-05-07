from typing import List

class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        res: List[str] = []

        def dfs(curr: str, last_i: int, last_j: int, par: tuple[str, str]) -> None:
            balance = 0
            for i in range(last_i, len(curr)):
                c = curr[i]
                if c == par[0]:
                    balance += 1
                elif c == par[1]:
                    balance -= 1
                if balance >= 0:
                    continue

                for j in range(last_j, i + 1):
                    if curr[j] == par[1] and (j == last_j or curr[j - 1] != par[1]):
                        dfs(curr[:j] + curr[j + 1 :], i, j, par)
                return

            reversed_curr = curr[::-1]
            if par[0] == '(':
                dfs(reversed_curr, 0, 0, (')', '('))
            else:
                res.append(reversed_curr)

        dfs(s, 0, 0, ('(', ')'))
        return res
