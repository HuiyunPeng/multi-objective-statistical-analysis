class Solution:
    def maxProfit(self, k, prices):
        n = len(prices)
        if n < 2 or k == 0:
            return 0

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
                prev_buy = buy[t]
                candidate_buy = sell[t - 1] - price
                if candidate_buy > prev_buy:
                    prev_buy = candidate_buy
                    buy[t] = prev_buy
                candidate_sell = prev_buy + price
                if candidate_sell > sell[t]:
                    sell[t] = candidate_sell

        return sell[k]
