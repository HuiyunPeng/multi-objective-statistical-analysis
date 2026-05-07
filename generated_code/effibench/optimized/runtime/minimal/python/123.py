class Solution:
    def maxProfit(self, prices):
        hold1 = float("-inf")
        sell1 = 0
        hold2 = float("-inf")
        sell2 = 0

        for price in prices:
            hold1 = max(hold1, -price)
            sell1 = max(sell1, hold1 + price)
            hold2 = max(hold2, sell1 - price)
            sell2 = max(sell2, hold2 + price)

        return sell2
