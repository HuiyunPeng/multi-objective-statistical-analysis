from typing import List
import heapq

class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        events = []
        for left, right, height in buildings:
            events.append((left, -height, right))  # building start
            events.append((right, 0, 0))           # building end marker

        events.sort()
        res = []
        heap = [(0, float('inf'))]  # (-height, right)
        i = 0
        n = len(events)

        while i < n:
            x = events[i][0]

            # Process all events at the same x
            while i < n and events[i][0] == x:
                _, neg_h, right = events[i]
                if neg_h != 0:
                    heapq.heappush(heap, (neg_h, right))
                i += 1

            # Remove buildings that have ended by x
            while heap and heap[0][1] <= x:
                heapq.heappop(heap)

            curr_height = -heap[0][0]
            if not res or res[-1][1] != curr_height:
                res.append([x, curr_height])

        return res
