class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)

        dp = [False] * (m + 1)
        dp[0] = True

        for j in range(2, m + 1):
            if p[j - 1] == '*':
                dp[j] = dp[j - 2]

        for i in range(1, n + 1):
            new = [False] * (m + 1)
            ch = s[i - 1]

            for j in range(1, m + 1):
                pj = p[j - 1]

                if pj == '*':
                    new[j] = new[j - 2]
                    prev = p[j - 2]
                    if prev == '.' or prev == ch:
                        new[j] = new[j] or dp[j]
                else:
                    if pj == '.' or pj == ch:
                        new[j] = dp[j - 1]

            dp = new

        return dp[m]
