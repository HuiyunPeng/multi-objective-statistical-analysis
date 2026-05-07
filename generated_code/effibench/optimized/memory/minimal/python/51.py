from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        res: List[List[str]] = []
        cols = [0] * n
        rows = ['.' * i + 'Q' + '.' * (n - i - 1) for i in range(n)]
        full = (1 << n) - 1

        def dfs(r: int, used_cols: int, diag1: int, diag2: int) -> None:
            if r == n:
                res.append([rows[cols[i]] for i in range(n)])
                return

            available = full & ~(used_cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                c = bit.bit_length() - 1
                cols[r] = c
                dfs(
                    r + 1,
                    used_cols | bit,
                    ((diag1 | bit) << 1) & full,
                    (diag2 | bit) >> 1,
                )

        dfs(0, 0, 0, 0)
        return res
