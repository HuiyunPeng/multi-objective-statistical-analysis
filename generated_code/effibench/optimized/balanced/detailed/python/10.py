class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        m, n = len(s), len(p)
        memo = {}

        def dfs(i: int, j: int) -> bool:
            key = (i, j)
            if key in memo:
                return memo[key]

            if j == n:
                return i == m

            first_match = i < m and (p[j] == s[i] or p[j] == ".")

            if j + 1 < n and p[j + 1] == "*":
                ans = dfs(i, j + 2) or (first_match and dfs(i + 1, j))
            else:
                ans = first_match and dfs(i + 1, j + 1)

            memo[key] = ans
            return ans

        return dfs(0, 0)
