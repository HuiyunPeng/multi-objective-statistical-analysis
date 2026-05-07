class Solution:
    def minCostII(self, costs):
        if not costs or not costs[0]:
            return 0

        k = len(costs[0])
        prev_min1 = prev_min2 = 0
        prev_idx1 = -1

        for row in costs:
            curr_min1 = curr_min2 = float('inf')
            curr_idx1 = -1

            for color in range(k):
                base = prev_min2 if color == prev_idx1 else prev_min1
                total = row[color] + base

                if total < curr_min1:
                    curr_min2 = curr_min1
                    curr_min1 = total
                    curr_idx1 = color
                elif total < curr_min2:
                    curr_min2 = total

            prev_min1, prev_min2, prev_idx1 = curr_min1, curr_min2, curr_idx1

        return prev_min1
