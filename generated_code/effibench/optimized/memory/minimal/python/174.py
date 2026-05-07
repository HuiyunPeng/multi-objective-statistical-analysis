class Solution:
    def calculateMinimumHP(self, dungeon):
        m, n = len(dungeon), len(dungeon[0])
        INF = float('inf')

        # Use O(min(m, n)) extra memory.
        if n <= m:
            dp = [INF] * (n + 1)
            dp[n - 1] = 1
            for i in range(m - 1, -1, -1):
                for j in range(n - 1, -1, -1):
                    need = min(dp[j], dp[j + 1]) - dungeon[i][j]
                    dp[j] = 1 if need <= 1 else need
            return dp[0]
        else:
            dp = [INF] * (m + 1)
            dp[m - 1] = 1
            for j in range(n - 1, -1, -1):
                for i in range(m - 1, -1, -1):
                    need = min(dp[i], dp[i + 1]) - dungeon[i][j]
                    dp[i] = 1 if need <= 1 else need
            return dp[0]
