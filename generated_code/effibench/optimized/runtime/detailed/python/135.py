class Solution:
    def candy(self, ratings):
        n = len(ratings)
        if n == 1:
            return 1

        total = 1
        up = down = peak = 0

        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                up += 1
                peak = up
                down = 0
                total += 1 + up
            elif ratings[i] == ratings[i - 1]:
                up = down = peak = 0
                total += 1
            else:
                up = 0
                down += 1
                total += 1 + down - (1 if peak >= down else 0)

        return total
