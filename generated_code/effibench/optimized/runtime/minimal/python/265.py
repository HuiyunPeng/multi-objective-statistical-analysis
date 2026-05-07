class Solution:
    def minCostII(self, costs):
        if not costs or not costs[0]:
            return 0

        k = len(costs[0])
        prev = costs[0][:]

        for i in range(1, len(costs)):
            min1 = float("inf")
            min2 = float("inf")
            min1_idx = -1

            for c in range(k):
                val = prev[c]
                if val < min1:
                    min2 = min1
                    min1 = val
                    min1_idx = c
                elif val < min2:
                    min2 = val

            curr = [0] * k
            for c in range(k):
                curr[c] = costs[i][c] + (min2 if c == min1_idx else min1)
            prev = curr

        return min(prev)
