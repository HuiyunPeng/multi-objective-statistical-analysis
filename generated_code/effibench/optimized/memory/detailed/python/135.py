class Solution:
    def candy(self, ratings):
        n = len(ratings)
        if n <= 1:
            return n

        candies = 0
        up = 0
        down = 0
        old_slope = 0

        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                new_slope = 1
            elif ratings[i] < ratings[i - 1]:
                new_slope = -1
            else:
                new_slope = 0

            if (old_slope > 0 and new_slope == 0) or (old_slope < 0 and new_slope >= 0):
                candies += up * (up + 1) // 2
                candies += down * (down + 1) // 2
                candies += max(up, down)
                up = 0
                down = 0

            if new_slope > 0:
                up += 1
            elif new_slope < 0:
                down += 1
            else:
                candies += 1

            old_slope = new_slope

        candies += up * (up + 1) // 2
        candies += down * (down + 1) // 2
        candies += max(up, down) + 1

        return candies
