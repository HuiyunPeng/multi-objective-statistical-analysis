class Solution:
    def minCostII(self, costs):
        if not costs or not costs[0]:
            return 0

        k = len(costs[0])
        prev = costs[0][:]

        for i in range(1, len(costs)):
            min1 = min2 = float('inf')
            idx1 = -1

            for c, val in enumerate(prev):
                if val < min1:
                    min2 = min1
                    min1 = val
                    idx1 = c
                elif val < min2:
                    min2 = val

            curr = [0] * k
            row = costs[i]
            for c in range(k):
                curr[c] = row[c] + (min2 if c == idx1 else min1)

            prev = curr

        return min(prev)
