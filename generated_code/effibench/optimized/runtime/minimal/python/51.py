class Solution:
    def solveNQueens(self, n: int):
        mask = (1 << n) - 1
        row_templates = ["." * c + "Q" + "." * (n - c - 1) for c in range(n)]
        result = []
        placement = [0] * n

        def dfs(row: int, cols: int, diag1: int, diag2: int) -> None:
            if row == n:
                result.append([row_templates[c] for c in placement])
                return

            available = mask & ~(cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                col = bit.bit_length() - 1
                placement[row] = col
                dfs(row + 1, cols | bit, ((diag1 | bit) << 1) & mask, (diag2 | bit) >> 1)

        dfs(0, 0, 0, 0)
        return result
