import heapq

class Solution:
    def getSkyline(self, buildings):
        n = len(buildings)
        res = []
        heap = []  # (-height, right)
        i = 0

        while i < n or heap:
            if not heap or (i < n and buildings[i][0] <= heap[0][1]):
                x = buildings[i][0]
                while i < n and buildings[i][0] == x:
                    left, right, height = buildings[i]
                    heapq.heappush(heap, (-height, right))
                    i += 1
            else:
                x = heap[0][1]

            while heap and heap[0][1] <= x:
                heapq.heappop(heap)

            curr_height = -heap[0][0] if heap else 0
            if not res or res[-1][1] != curr_height:
                res.append([x, curr_height])

        return res
