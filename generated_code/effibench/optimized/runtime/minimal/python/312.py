class Solution:
    def maxCoins(self, nums):
        vals = [1]
        vals.extend(x for x in nums if x > 0)
        vals.append(1)

        m = len(vals)
        if m <= 2:
            return 0

        dp = [[0] * m for _ in range(m)]

        for gap in range(2, m):
            for left in range(m - gap):
                right = left + gap
                left_val = vals[left]
                right_val = vals[right]
                best = 0
                row_left = dp[left]

                for k in range(left + 1, right):
                    coins = row_left[k] + dp[k][right] + left_val * vals[k] * right_val
                    if coins > best:
                        best = coins

                row_left[right] = best

        return dp[0][m - 1]
