class Solution:
    def maxProfit(self, k, prices):
        n = len(prices)
        if k <= 0 or n < 2:
            return 0

        # If k is large enough, this becomes the unlimited transactions case.
        if k >= n // 2:
            profit = 0
            prev = prices[0]
            for i in range(1, n):
                p = prices[i]
                if p > prev:
                    profit += p - prev
                prev = p
            return profit

        buy = [-10**15] * (k + 1)
        sell = [0] * (k + 1)

        for p in prices:
            for t in range(1, k + 1):
                v = sell[t - 1] - p
                if v > buy[t]:
                    buy[t] = v
                v = buy[t] + p
                if v > sell[t]:
                    sell[t] = v

        return sell[k]
