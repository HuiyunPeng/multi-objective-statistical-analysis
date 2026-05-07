import heapq

class Solution:
    def getSkyline(self, buildings):
        n = len(buildings)
        res = []
        
        # Max-heap by height using negative heights; stores (-height, right)
        # Sentinel ground level to avoid empty-heap checks.
        heap = [(0, float('inf'))]
        
        i = 0
        prev_height = 0
        
        while i < n or len(heap) > 1:
            # Decide next x:
            # - next building start, if it comes before or at current tallest end
            # - otherwise, current tallest building's end
            if i < n and (len(heap) == 1 or buildings[i][0] <= heap[0][1]):
                x = buildings[i][0]
                while i < n and buildings[i][0] == x:
                    left, right, height = buildings[i]
                    heapq.heappush(heap, (-height, right))
                    i += 1
            else:
                x = heap[0][1]
            
            # Remove all buildings that have ended by x
            while heap and heap[0][1] <= x:
                heapq.heappop(heap)
            
            curr_height = -heap[0][0]
            if curr_height != prev_height:
                res.append([x, curr_height])
                prev_height = curr_height
        
        return res
