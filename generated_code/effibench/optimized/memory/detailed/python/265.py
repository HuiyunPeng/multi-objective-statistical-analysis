class Solution:
    def minCostII(self, costs):
        if not costs or not costs[0]:
            return 0

        prev_row = costs[0]
        min1 = min2 = -1

        for c, v in enumerate(prev_row):
            if min1 == -1 or v < prev_row[min1]:
                min2 = min1
                min1 = c
            elif min2 == -1 or v < prev_row[min2]:
                min2 = c

        for i in range(1, len(costs)):
            row = costs[i]
            new1 = new2 = -1

            best1 = prev_row[min1]
            best2 = prev_row[min2]

            for c in range(len(row)):
                row[c] += best2 if c == min1 else best1

                if new1 == -1 or row[c] < row[new1]:
                    new2 = new1
                    new1 = c
                elif new2 == -1 or row[c] < row[new2]:
                    new2 = c

            prev_row = row
            min1, min2 = new1, new2

        return prev_row[min1]
