class Solution:
    def solveNQueens(self, n: int):
        mask = (1 << n) - 1
        positions = [0] * n
        row_strings = ['.' * c + 'Q' + '.' * (n - 1 - c) for c in range(n)]
        result = []

        def dfs(row: int, cols: int, diag1: int, diag2: int) -> None:
            if row == n:
                result.append([row_strings[c] for c in positions])
                return

            available = mask & ~(cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                positions[row] = bit.bit_length() - 1
                dfs(row + 1, cols | bit, ((diag1 | bit) << 1) & mask, (diag2 | bit) >> 1)

        dfs(0, 0, 0, 0)
        return result
