class Solution:
    def maxNumber(self, nums1, nums2, k):
        m, n = len(nums1), len(nums2)

        cache1 = {0: []}
        cache2 = {0: []}

        def pick_max(nums, length, cache):
            if length in cache:
                return cache[length]
            if length == len(nums):
                cache[length] = nums[:]
                return cache[length]

            drop = len(nums) - length
            stack = []

            for x in nums:
                while drop and stack and stack[-1] < x:
                    stack.pop()
                    drop -= 1
                if len(stack) < length:
                    stack.append(x)
                else:
                    drop -= 1

            cache[length] = stack
            return stack

        def merge(a, b):
            la, lb = len(a), len(b)

            # gt[i][j] == 1 iff a[i:] > b[j:] lexicographically
            gt = [bytearray(lb + 1) for _ in range(la + 1)]

            for i in range(la - 1, -1, -1):
                row = gt[i]
                next_row = gt[i + 1]
                ai = a[i]
                row[lb] = 1  # non-empty suffix > empty suffix

                for j in range(lb - 1, -1, -1):
                    bj = b[j]
                    if ai > bj:
                        row[j] = 1
                    elif ai < bj:
                        row[j] = 0
                    else:
                        row[j] = next_row[j + 1]

            res = [0] * (la + lb)
            i = j = t = 0

            while i < la or j < lb:
                if j == lb or (i < la and gt[i][j]):
                    res[t] = a[i]
                    i += 1
                else:
                    res[t] = b[j]
                    j += 1
                t += 1

            return res

        best = []
        start = max(0, k - n)
        end = min(k, m)

        for take1 in range(start, end + 1):
            take2 = k - take1
            part1 = pick_max(nums1, take1, cache1)
            part2 = pick_max(nums2, take2, cache2)
            candidate = merge(part1, part2)
            if candidate > best:
                best = candidate

        return best
