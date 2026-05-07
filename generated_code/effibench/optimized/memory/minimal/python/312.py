class Solution:
    def maxCoins(self, nums):
        vals = [1]
        for x in nums:
            if x > 0:
                vals.append(x)
        vals.append(1)

        m = len(vals)
        if m <= 2:
            return 0

        # dp[left][gap] stores the best result for interval (left, left + gap)
        # using triangular storage to save memory.
        dp = [[0] * (m - i) for i in range(m)]

        for gap in range(2, m):
            limit = m - gap
            for left in range(limit):
                right = left + gap
                base = vals[left] * vals[right]
                row_left = dp[left]
                best = 0

                for k in range(left + 1, right):
                    total = row_left[k - left] + dp[k][right - k] + base * vals[k]
                    if total > best:
                        best = total

                row_left[gap] = best

        return dp[0][m - 1]
