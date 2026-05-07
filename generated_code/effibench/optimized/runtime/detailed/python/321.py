from typing import List

class Solution:
    def maxNumber(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        def pick_max(nums: List[int], length: int) -> List[int]:
            if length == 0:
                return []
            drop = len(nums) - length
            stack = []
            for digit in nums:
                while drop and stack and stack[-1] < digit:
                    stack.pop()
                    drop -= 1
                stack.append(digit)
            return stack[:-drop] if drop else stack

        def merge_max(a: List[int], b: List[int]) -> List[int]:
            la, lb = len(a), len(b)
            if la == 0:
                return b
            if lb == 0:
                return a

            # lcp[i][j] = longest common prefix length of a[i:] and b[j:]
            lcp = [[0] * (lb + 1) for _ in range(la + 1)]
            for i in range(la - 1, -1, -1):
                ai = a[i]
                row = lcp[i]
                next_row = lcp[i + 1]
                for j in range(lb - 1, -1, -1):
                    if ai == b[j]:
                        row[j] = next_row[j + 1] + 1

            res = [0] * (la + lb)
            i = j = t = 0

            while i < la and j < lb:
                common = lcp[i][j]
                if j + common == lb or (i + common < la and a[i + common] > b[j + common]):
                    res[t] = a[i]
                    i += 1
                else:
                    res[t] = b[j]
                    j += 1
                t += 1

            while i < la:
                res[t] = a[i]
                i += 1
                t += 1
            while j < lb:
                res[t] = b[j]
                j += 1
                t += 1

            return res

        start = max(0, k - len(nums2))
        end = min(k, len(nums1))

        best = []
        for take1 in range(start, end + 1):
            candidate = merge_max(
                pick_max(nums1, take1),
                pick_max(nums2, k - take1)
            )
            if candidate > best:
                best = candidate

        return best
