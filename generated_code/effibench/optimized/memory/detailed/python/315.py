class Solution:
    def countSmaller(self, nums):
        n = len(nums)
        res = [0] * n

        # nums[i] in [-10000, 10000]
        # Map value v to index v + 10001 in Fenwick tree (1-based).
        size = 20001
        tree = [0] * (size + 1)

        for i in range(n - 1, -1, -1):
            idx = nums[i] + 10001

            # Query count of values strictly smaller than nums[i]
            s = 0
            j = idx - 1
            while j > 0:
                s += tree[j]
                j -= j & -j
            res[i] = s

            # Update Fenwick tree with nums[i]
            j = idx
            while j <= size:
                tree[j] += 1
                j += j & -j

        return res
