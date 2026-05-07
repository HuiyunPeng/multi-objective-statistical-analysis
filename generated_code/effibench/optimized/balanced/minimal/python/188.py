class Solution:
    def maxProfit(self, k, prices):
        n = len(prices)
        if k == 0 or n < 2:
            return 0

        # If transactions are effectively unlimited, take every profitable rise.
        if k >= n // 2:
            profit = 0
            for i in range(1, n):
                if prices[i] > prices[i - 1]:
                    profit += prices[i] - prices[i - 1]
            return profit

        neg_inf = -10**15
        buy = [neg_inf] * (k + 1)
        sell = [0] * (k + 1)

        for price in prices:
            for t in range(1, k + 1):
                buy[t] = max(buy[t], sell[t - 1] - price)
                sell[t] = max(sell[t], buy[t] + price)

        return sell[k]
