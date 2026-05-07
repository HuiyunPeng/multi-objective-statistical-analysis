class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n = len(s)
        m = len(t)
        
        if m > n:
            return 0
        if m == 0:
            return 1
        
        dp = [0] * (m + 1)
        dp[0] = 1
        
        for i in range(n):
            limit = m if i + 1 >= m else i + 1
            sc = s[i]
            for j in range(limit, 0, -1):
                if sc == t[j - 1]:
                    dp[j] += dp[j - 1]
        
        return dp[m]
