from typing import List
import heapq


class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        events = []
        for left, right, height in buildings:
            events.append((left, -height, right))  # building start
            events.append((right, 0, 0))          # building end marker

        events.sort()

        res = []
        heap = [(0, float("inf"))]  # (-height, right)
        prev_height = 0
        i = 0
        m = len(events)

        while i < m:
            x = events[i][0]

            while i < m and events[i][0] == x:
                _, neg_height, right = events[i]
                if neg_height:
                    heapq.heappush(heap, (neg_height, right))
                i += 1

            while heap and heap[0][1] <= x:
                heapq.heappop(heap)

            curr_height = -heap[0][0]
            if curr_height != prev_height:
                res.append([x, curr_height])
                prev_height = curr_height

        return res
