class Solution:
    def maxCoins(self, nums):
        # Bursting zero-value balloons can always be done first for 0 coins,
        # so they can be removed without changing the optimal answer.
        vals = [1]
        for x in nums:
            if x:
                vals.append(x)
        vals.append(1)

        m = len(vals)
        if m <= 2:
            return 0

        # Flattened DP table: dp[left * m + right] stores the best result
        # for bursting all balloons strictly between left and right.
        dp = [0] * (m * m)
        a = vals

        for gap in range(2, m):
            for left in range(m - gap):
                right = left + gap
                left_row = left * m
                edge_prod = a[left] * a[right]
                best = 0

                for k in range(left + 1, right):
                    total = dp[left_row + k] + dp[k * m + right] + edge_prod * a[k]
                    if total > best:
                        best = total

                dp[left_row + right] = best

        return dp[m - 1]
