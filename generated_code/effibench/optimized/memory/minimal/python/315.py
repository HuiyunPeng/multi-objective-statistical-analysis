class Solution:
    def countSmaller(self, nums):
        size = 20003  # enough for values in [-10000, 10000] mapped to [1, 20001]
        bit = [0] * size

        def update(i):
            while i < size:
                bit[i] += 1
                i += i & -i

        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s

        n = len(nums)
        res = [0] * n
        offset = 10001

        for i in range(n - 1, -1, -1):
            idx = nums[i] + offset
            res[i] = query(idx - 1)
            update(idx)

        return res
