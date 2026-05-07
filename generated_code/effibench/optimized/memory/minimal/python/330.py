class Solution:
    def minPatches(self, nums, n):
        patches = 0
        miss = 1
        i = 0
        m = len(nums)

        while miss <= n:
            if i < m and nums[i] <= miss:
                miss += nums[i]
                i += 1
            else:
                miss += miss
                patches += 1

        return patches
