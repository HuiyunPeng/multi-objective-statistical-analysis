class Solution:
    def countSmaller(self, nums):
        n = len(nums)
        res = [0] * n

        # Constraints guarantee nums[i] in [-10^4, 10^4]
        offset = 10001
        size = 20003  # enough for 1-based Fenwick indices

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

        for i in range(n - 1, -1, -1):
            idx = nums[i] + offset
            res[i] = query(idx - 1)
            update(idx)

        return res
