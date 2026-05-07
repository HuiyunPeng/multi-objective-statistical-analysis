from typing import List

class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        vals = [1] + [x for x in nums if x > 0] + [1]
        n = len(vals)
        
        if n <= 2:
            return 0
        
        dp = [[0] * n for _ in range(n)]
        
        for gap in range(2, n):
            for left in range(n - gap):
                right = left + gap
                left_val = vals[left]
                right_val = vals[right]
                best = 0
                dp_left = dp[left]
                
                for k in range(left + 1, right):
                    coins = dp_left[k] + dp[k][right] + left_val * vals[k] * right_val
                    if coins > best:
                        best = coins
                
                dp_left[right] = best
        
        return dp[0][n - 1]
