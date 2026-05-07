class Solution:
    def totalNQueens(self, n: int) -> int:
        full = (1 << n) - 1

        def dfs(cols: int, diag1: int, diag2: int) -> int:
            if cols == full:
                return 1

            count = 0
            available = full & ~(cols | diag1 | diag2)
            while available:
                bit = available & -available
                available -= bit
                count += dfs(
                    cols | bit,
                    ((diag1 | bit) << 1) & full,
                    (diag2 | bit) >> 1,
                )
            return count

        half = n // 2
        total = 0

        for col in range(half):
            bit = 1 << col
            total += dfs(bit, (bit << 1) & full, bit >> 1)
        total *= 2

        if n % 2:
            bit = 1 << half
            total += dfs(bit, (bit << 1) & full, bit >> 1)

        return total
