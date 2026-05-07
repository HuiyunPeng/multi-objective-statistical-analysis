class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)

        # dp[j] = whether s[i+1:] matches p[j:] for the previous iteration of i
        dp = [False] * (m + 1)
        dp[m] = True

        # Initialize for empty string s[n:]
        for j in range(m - 1, -1, -1):
            if p[j] == '*':
                continue
            if j + 1 < m and p[j + 1] == '*':
                dp[j] = dp[j + 2]

        for i in range(n - 1, -1, -1):
            curr = [False] * (m + 1)
            for j in range(m - 1, -1, -1):
                if p[j] == '*':
                    continue

                first_match = p[j] == '.' or p[j] == s[i]

                if j + 1 < m and p[j + 1] == '*':
                    curr[j] = curr[j + 2] or (first_match and dp[j])
                else:
                    curr[j] = first_match and dp[j + 1]

            dp = curr

        return dp[0]
