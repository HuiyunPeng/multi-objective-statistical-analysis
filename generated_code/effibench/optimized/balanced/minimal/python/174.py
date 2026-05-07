class Solution:
    def calculateMinimumHP(self, dungeon):
        m, n = len(dungeon), len(dungeon[0])
        INF = 10**18
        
        dp = [INF] * (n + 1)
        dp[n - 1] = 1
        
        for i in range(m - 1, -1, -1):
            dp[n] = INF
            for j in range(n - 1, -1, -1):
                need = min(dp[j], dp[j + 1]) - dungeon[i][j]
                dp[j] = 1 if need <= 1 else need
        
        return dp[0]
