class Solution:
    def solveNQueens(self, n: int):
        full = (1 << n) - 1
        bit_to_col = {1 << i: i for i in range(n)}
        row_templates = ['.' * i + 'Q' + '.' * (n - i - 1) for i in range(n)]
        
        res = []
        path = []

        def dfs(row: int, cols: int, diag1: int, diag2: int):
            if row == n:
                res.append([row_templates[c] for c in path])
                return

            available = full & ~(cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                path.append(bit_to_col[bit])
                dfs(
                    row + 1,
                    cols | bit,
                    ((diag1 | bit) << 1) & full,
                    (diag2 | bit) >> 1,
                )
                path.pop()

        dfs(0, 0, 0, 0)
        return res
