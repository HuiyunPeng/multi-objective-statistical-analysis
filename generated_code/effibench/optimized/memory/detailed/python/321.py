class Solution:
    def maxNumber(self, nums1, nums2, k):
        m, n = len(nums1), len(nums2)
        start = max(0, k - n)
        end = min(k, m)

        best = []

        for take1 in range(start, end + 1):
            part1 = self._pick(nums1, take1)
            part2 = self._pick(nums2, k - take1)
            candidate = self._merge(part1, part2, k)
            if candidate > best:
                best = candidate

        return best

    def _pick(self, nums, t):
        if t == 0:
            return []
        if t == len(nums):
            return nums

        drop = len(nums) - t
        stack = [0] * t
        size = 0

        for d in nums:
            while size and drop and stack[size - 1] < d:
                size -= 1
                drop -= 1
            if size < t:
                stack[size] = d
                size += 1
            else:
                drop -= 1

        return stack

    def _greater(self, a, i, b, j):
        la, lb = len(a), len(b)
        while i < la and j < lb and a[i] == b[j]:
            i += 1
            j += 1
        return j == lb or (i < la and a[i] > b[j])

    def _merge(self, a, b, k):
        res = [0] * k
        i = j = r = 0
        la, lb = len(a), len(b)

        while i < la or j < lb:
            if self._greater(a, i, b, j):
                res[r] = a[i]
                i += 1
            else:
                res[r] = b[j]
                j += 1
            r += 1

        return res
