class Solution:
    def calculateMinimumHP(self, dungeon):
        n = len(dungeon[0])
        inf = float('inf')
        dp = [inf] * (n + 1)
        dp[n - 1] = 1

        for i in range(len(dungeon) - 1, -1, -1):
            row = dungeon[i]
            for j in range(n - 1, -1, -1):
                need = min(dp[j], dp[j + 1]) - row[j]
                dp[j] = 1 if need <= 1 else need

        return dp[0]
