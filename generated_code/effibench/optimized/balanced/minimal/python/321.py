class Solution:
    def maxNumber(self, nums1, nums2, k):
        def pick_max(nums, length):
            drop = len(nums) - length
            stack = []
            for x in nums:
                while drop and stack and stack[-1] < x:
                    stack.pop()
                    drop -= 1
                stack.append(x)
            if drop:
                return stack[:-drop]
            return stack

        def greater(a, i, b, j):
            la, lb = len(a), len(b)
            while i < la and j < lb and a[i] == b[j]:
                i += 1
                j += 1
            return j == lb or (i < la and a[i] > b[j])

        def merge(a, b):
            i = j = 0
            la, lb = len(a), len(b)
            res = []
            while i < la or j < lb:
                if greater(a, i, b, j):
                    res.append(a[i])
                    i += 1
                else:
                    res.append(b[j])
                    j += 1
            return res

        m, n = len(nums1), len(nums2)
        start = max(0, k - n)
        end = min(k, m)

        best = []
        for i in range(start, end + 1):
            part1 = pick_max(nums1, i)
            part2 = pick_max(nums2, k - i)
            candidate = merge(part1, part2)
            if not best or greater(candidate, 0, best, 0):
                best = candidate

        return best
