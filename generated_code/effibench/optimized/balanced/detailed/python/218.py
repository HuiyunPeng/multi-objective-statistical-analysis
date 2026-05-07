from typing import List
import heapq


class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        n = len(buildings)
        i = 0
        live = []  # max-heap by height: (-height, right)
        res = []

        while i < n or live:
            if not live or (i < n and buildings[i][0] <= live[0][1]):
                x = buildings[i][0]
                while i < n and buildings[i][0] == x:
                    _, right, height = buildings[i]
                    heapq.heappush(live, (-height, right))
                    i += 1
            else:
                x = live[0][1]

            while live and live[0][1] <= x:
                heapq.heappop(live)

            height = -live[0][0] if live else 0
            if not res or res[-1][1] != height:
                res.append([x, height])

        return res
