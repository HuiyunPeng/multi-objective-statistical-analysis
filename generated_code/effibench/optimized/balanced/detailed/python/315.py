class Solution:
    def countSmaller(self, nums):
        n = len(nums)
        res = [0] * n

        # Value range: [-10000, 10000]
        offset = 10001
        size = 20002  # ranks 1..20001
        bit = [0] * (size + 1)

        def update(i):
            while i <= size:
                bit[i] += 1
                i += i & -i

        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s

        for idx in range(n - 1, -1, -1):
            rank = nums[idx] + offset
            res[idx] = query(rank - 1)
            update(rank)

        return res
