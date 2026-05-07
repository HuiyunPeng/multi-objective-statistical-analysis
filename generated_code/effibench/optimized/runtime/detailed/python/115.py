class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        if m > n:
            return 0
        if m == 0:
            return 1

        # positions[c] holds all 1-based indices j such that t[j-1] == c,
        # stored in descending order so dp updates remain correct in-place.
        positions = {}
        for j, ch in enumerate(t, 1):
            positions.setdefault(ch, []).append(j)
        for ch in positions:
            positions[ch].reverse()

        dp = [0] * (m + 1)
        dp[0] = 1

        for ch in s:
            if ch in positions:
                for j in positions[ch]:
                    dp[j] += dp[j - 1]

        return dp[m]
