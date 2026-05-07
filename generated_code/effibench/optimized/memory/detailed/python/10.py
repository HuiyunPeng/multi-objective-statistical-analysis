class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        m = len(p)
        dp = [False] * (m + 1)
        dp[0] = True

        for j in range(2, m + 1):
            if p[j - 1] == '*':
                dp[j] = dp[j - 2]

        for ch in s:
            prev = dp[0]
            dp[0] = False

            for j in range(1, m + 1):
                old = dp[j]
                pj = p[j - 1]

                if pj == '*':
                    prev_pat = p[j - 2]
                    dp[j] = dp[j - 2] or (old and (prev_pat == '.' or prev_pat == ch))
                else:
                    dp[j] = prev and (pj == '.' or pj == ch)

                prev = old

        return dp[m]
