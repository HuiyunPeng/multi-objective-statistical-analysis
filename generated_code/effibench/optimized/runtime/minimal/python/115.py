class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        if m > n:
            return 0
        if m == 0:
            return 1

        dp = [0] * (m + 1)
        dp[0] = 1

        for i, cs in enumerate(s, 1):
            upper = min(i, m)
            for j in range(upper, 0, -1):
                if cs == t[j - 1]:
                    dp[j] += dp[j - 1]

        return dp[m]
