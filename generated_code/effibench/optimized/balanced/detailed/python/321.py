class Solution:
    def _pick(self, nums, k):
        if k == 0:
            return []
        drop = len(nums) - k
        stack = [0] * len(nums)
        size = 0

        for x in nums:
            while drop and size and stack[size - 1] < x:
                size -= 1
                drop -= 1
            stack[size] = x
            size += 1

        return stack[:k]

    def _merge(self, a, b):
        la, lb = len(a), len(b)
        if la == 0:
            return b
        if lb == 0:
            return a

        combined = a + [-1] + b
        n = len(combined)

        # Prefix-doubling suffix ranks for exact O(1) suffix comparisons during merge.
        rank = [x + 1 for x in combined]  # sentinel -1 becomes 0
        idx = list(range(n))
        tmp = [0] * n
        step = 1

        while True:
            rk = rank
            idx.sort(key=lambda i, rk=rk, step=step, n=n: (rk[i], rk[i + step] if i + step < n else -1))

            prev = idx[0]
            tmp[prev] = 0
            r = 0

            for t in range(1, n):
                cur = idx[t]
                if rk[prev] != rk[cur] or (rk[prev + step] if prev + step < n else -1) != (rk[cur + step] if cur + step < n else -1):
                    r += 1
                tmp[cur] = r
                prev = cur

            rank, tmp = tmp, rank
            if r == n - 1:
                break
            step <<= 1

        res = [0] * (la + lb)
        i = j = p = 0
        offset = la + 1

        while i < la and j < lb:
            if rank[i] > rank[offset + j]:
                res[p] = a[i]
                i += 1
            else:
                res[p] = b[j]
                j += 1
            p += 1

        if i < la:
            res[p:] = a[i:]
        else:
            res[p:] = b[j:]

        return res

    def maxNumber(self, nums1, nums2, k):
        m, n = len(nums1), len(nums2)
        start = max(0, k - n)
        end = min(k, m)

        best = []
        pick = self._pick
        merge = self._merge

        for x in range(start, end + 1):
            a = pick(nums1, x)
            b = pick(nums2, k - x)
            cand = merge(a, b)
            if cand > best:
                best = cand

        return best
