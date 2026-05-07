class Solution:
    def maxProfit(self, prices):
        buy1 = float("-inf")
        sell1 = 0
        buy2 = float("-inf")
        sell2 = 0

        for price in prices:
            if -price > buy1:
                buy1 = -price
            if buy1 + price > sell1:
                sell1 = buy1 + price
            if sell1 - price > buy2:
                buy2 = sell1 - price
            if buy2 + price > sell2:
                sell2 = buy2 + price

        return sell2
