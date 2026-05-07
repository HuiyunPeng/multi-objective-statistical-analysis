class Solution:
    def maxNumber(self, nums1, nums2, k):
        def pick_max_subsequence(nums, length):
            if length == 0:
                return []
            drop = len(nums) - length
            stack = []
            for digit in nums:
                while drop and stack and stack[-1] < digit:
                    stack.pop()
                    drop -= 1
                if len(stack) < length:
                    stack.append(digit)
                else:
                    drop -= 1
            return stack

        def build_suffix_ranks(a, b):
            # Ranks of suffixes in a + [-1] + b
            # Higher rank => lexicographically larger suffix.
            la = len(a)
            seq = [x + 1 for x in a]
            seq.append(0)  # separator smaller than any digit
            seq.extend(x + 1 for x in b)

            n = len(seq)
            rank = seq
            tmp = [0] * n
            sa = list(range(n))
            step = 1

            while step < n:
                r = rank
                sa.sort(key=lambda i, r=r, step=step, n=n: (r[i], r[i + step] if i + step < n else -1))

                prev = sa[0]
                tmp[prev] = 0
                new_rank = 0

                for idx in sa[1:]:
                    if r[idx] != r[prev] or (r[idx + step] if idx + step < n else -1) != (r[prev + step] if prev + step < n else -1):
                        new_rank += 1
                    tmp[idx] = new_rank
                    prev = idx

                rank, tmp = tmp, rank
                if new_rank == n - 1:
                    break
                step <<= 1

            return rank, la + 1

        def merge(a, b):
            if not a:
                return b[:]
            if not b:
                return a[:]

            rank, offset = build_suffix_ranks(a, b)
            la, lb = len(a), len(b)
            res = [0] * (la + lb)

            i = j = t = 0
            while i < la and j < lb:
                if rank[i] > rank[offset + j]:
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

        m, n = len(nums1), len(nums2)
        start = max(0, k - n)
        end = min(k, m)

        best = []
        for take1 in range(start, end + 1):
            part1 = pick_max_subsequence(nums1, take1)
            part2 = pick_max_subsequence(nums2, k - take1)
            candidate = merge(part1, part2)
            if candidate > best:
                best = candidate

        return best
