from typing import List

class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        offset = 10001
        size = 20003  # covers values from -10000 to 10000 with 1-based indexing
        bit = [0] * size

        def update(i: int) -> None:
            while i < size:
                bit[i] += 1
                i += i & -i

        def query(i: int) -> int:
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s

        n = len(nums)
        ans = [0] * n

        for i in range(n - 1, -1, -1):
            idx = nums[i] + offset + 1
            ans[i] = query(idx - 1)
            update(idx)

        return ans
