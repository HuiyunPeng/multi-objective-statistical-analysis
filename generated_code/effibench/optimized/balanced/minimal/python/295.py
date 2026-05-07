import heapq


class MedianFinder:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.small = []  # max-heap via negated values
        self.large = []  # min-heap

    def addNum(self, num: int) -> None:
        """
        Add an integer number from the data stream to the data structure.
        """
        if not self.small or num <= -self.small[0]:
            heapq.heappush(self.small, -num)
        else:
            heapq.heappush(self.large, num)

        if len(self.small) > len(self.large) + 1:
            heapq.heappush(self.large, -heapq.heappop(self.small))
        elif len(self.large) > len(self.small):
            heapq.heappush(self.small, -heapq.heappop(self.large))

    def findMedian(self) -> float:
        """
        Return the median of all elements so far.
        """
        if len(self.small) > len(self.large):
            return float(-self.small[0])
        return (-self.small[0] + self.large[0]) / 2.0
