class Solution:
    def maxProfit(self, prices):
        buy1 = float('inf')
        profit1 = 0
        buy2 = float('inf')
        profit2 = 0

        for price in prices:
            if price < buy1:
                buy1 = price
            if price - buy1 > profit1:
                profit1 = price - buy1

            effective_price = price - profit1
            if effective_price < buy2:
                buy2 = effective_price
            if price - buy2 > profit2:
                profit2 = price - buy2

        return profit2
