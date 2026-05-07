class Solution:
    def maxProfit(self, k, prices):
        n = len(prices)
        if n < 2 or k == 0:
            return 0

        # If k is large enough, this becomes unlimited transactions.
        if k >= n // 2:
            profit = 0
            for i in range(1, n):
                if prices[i] > prices[i - 1]:
                    profit += prices[i] - prices[i - 1]
            return profit

        # buy[t]  = max profit after buying the t-th stock
        # sell[t] = max profit after selling the t-th stock
        buy = [-10**15] * (k + 1)
        sell = [0] * (k + 1)

        for price in prices:
            for t in range(1, k + 1):
                if sell[t - 1] - price > buy[t]:
                    buy[t] = sell[t - 1] - price
                if buy[t] + price > sell[t]:
                    sell[t] = buy[t] + price

        return sell[k]
