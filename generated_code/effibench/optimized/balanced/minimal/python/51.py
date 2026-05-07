class Solution:
    def solveNQueens(self, n: int):
        results = []
        placement = [0] * n
        row_templates = ['.' * c + 'Q' + '.' * (n - c - 1) for c in range(n)]
        full = (1 << n) - 1

        def dfs(row: int, cols: int, diag1: int, diag2: int):
            if row == n:
                results.append([row_templates[c] for c in placement])
                return

            available = full & ~(cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                col = bit.bit_length() - 1
                placement[row] = col
                dfs(
                    row + 1,
                    cols | bit,
                    ((diag1 | bit) << 1) & full,
                    (diag2 | bit) >> 1,
                )

        dfs(0, 0, 0, 0)
        return results
