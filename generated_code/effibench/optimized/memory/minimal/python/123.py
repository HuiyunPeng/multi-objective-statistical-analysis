class Solution:
    def maxProfit(self, prices):
        first_buy = float("-inf")
        first_sell = 0
        second_buy = float("-inf")
        second_sell = 0

        for price in prices:
            if -price > first_buy:
                first_buy = -price
            if first_buy + price > first_sell:
                first_sell = first_buy + price
            if first_sell - price > second_buy:
                second_buy = first_sell - price
            if second_buy + price > second_sell:
                second_sell = second_buy + price

        return second_sell
