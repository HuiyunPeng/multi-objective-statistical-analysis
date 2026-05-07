class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        dp = list(range(-1, n))  # dp[i] = min cuts for s[:i]

        for center in range(n):
            # Odd-length palindromes
            l = r = center
            while l >= 0 and r < n and s[l] == s[r]:
                new_cut = dp[l] + 1
                if new_cut < dp[r + 1]:
                    dp[r + 1] = new_cut
                l -= 1
                r += 1

            # Even-length palindromes
            l, r = center - 1, center
            while l >= 0 and r < n and s[l] == s[r]:
                new_cut = dp[l] + 1
                if new_cut < dp[r + 1]:
                    dp[r + 1] = new_cut
                l -= 1
                r += 1

        return dp[n]
