class Solution:
    def maxProfit(self, k, prices):
        n = len(prices)
        if n < 2 or k == 0:
            return 0

        # If k is large enough, this becomes the unlimited transactions case.
        if k >= n // 2:
            profit = 0
            for i in range(1, n):
                diff = prices[i] - prices[i - 1]
                if diff > 0:
                    profit += diff
            return profit

        buy = [-10**15] * (k + 1)
        sell = [0] * (k + 1)

        for price in prices:
            for t in range(1, k + 1):
                prev_sell = sell[t - 1]
                if prev_sell - price > buy[t]:
                    buy[t] = prev_sell - price
                if buy[t] + price > sell[t]:
                    sell[t] = buy[t] + price

        return sell[k]
