class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        if m > n:
            return 0
        if m == 0:
            return 1

        positions = {}
        for i, ch in enumerate(t, 1):
            if ch in positions:
                positions[ch].append(i)
            else:
                positions[ch] = [i]

        dp = [0] * (m + 1)
        dp[0] = 1

        for ch in s:
            if ch not in positions:
                continue
            for j in reversed(positions[ch]):
                dp[j] += dp[j - 1]

        return dp[m]
