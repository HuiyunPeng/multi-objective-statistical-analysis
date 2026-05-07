class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        # Ensure nums1 is the smaller array to keep binary search bounds minimal.
        if len(nums1) > len(nums2):
            nums1, nums2 = nums2, nums1

        m, n = len(nums1), len(nums2)
        total = m + n
        half = (total + 1) // 2

        left, right = 0, m

        while left <= right:
            i = (left + right) // 2
            j = half - i

            a_left = nums1[i - 1] if i > 0 else float("-inf")
            a_right = nums1[i] if i < m else float("inf")
            b_left = nums2[j - 1] if j > 0 else float("-inf")
            b_right = nums2[j] if j < n else float("inf")

            if a_left <= b_right and b_left <= a_right:
                if total % 2:
                    return float(a_left if a_left > b_left else b_left)
                left_max = a_left if a_left > b_left else b_left
                right_min = a_right if a_right < b_right else b_right
                return (left_max + right_min) / 2.0

            if a_left > b_right:
                right = i - 1
            else:
                left = i + 1

        return 0.0
