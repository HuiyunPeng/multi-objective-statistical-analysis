class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        if s1 == s2:
            return True

        n = len(s1)
        if n != len(s2):
            return False

        a = [ord(c) - 97 for c in s1]
        b = [ord(c) - 97 for c in s2]

        total = [0] * 26
        for i in range(n):
            total[a[i]] += 1
            total[b[i]] -= 1
        for v in total:
            if v:
                return False

        pref1 = [bytearray(26)]
        for v in a:
            row = pref1[-1][:]
            row[v] += 1
            pref1.append(row)

        pref2 = [bytearray(26)]
        for v in b:
            row = pref2[-1][:]
            row[v] += 1
            pref2.append(row)

        def same_counts(i1: int, i2: int, length: int) -> bool:
            p1l = pref1[i1]
            p1r = pref1[i1 + length]
            p2l = pref2[i2]
            p2r = pref2[i2 + length]
            for k in range(26):
                if p1r[k] - p1l[k] != p2r[k] - p2l[k]:
                    return False
            return True

        def same_substring(i1: int, i2: int, length: int) -> bool:
            for k in range(length):
                if a[i1 + k] != b[i2 + k]:
                    return False
            return True

        base = n + 1
        memo = {}

        def dfs(i1: int, i2: int, length: int) -> bool:
            key = (i1 * base + i2) * base + length
            if key in memo:
                return memo[key]

            if same_substring(i1, i2, length):
                memo[key] = True
                return True

            if not same_counts(i1, i2, length):
                memo[key] = False
                return False

            diff_no_swap = [0] * 26
            diff_swap = [0] * 26
            nz_no_swap = 0
            nz_swap = 0
            end2 = i2 + length

            for k in range(1, length):
                x = a[i1 + k - 1]
                y1 = b[i2 + k - 1]
                y2 = b[end2 - k]

                old = diff_no_swap[x]
                if old == 0:
                    nz_no_swap += 1
                diff_no_swap[x] = old + 1
                if diff_no_swap[x] == 0:
                    nz_no_swap -= 1

                old = diff_no_swap[y1]
                if old == 0:
                    nz_no_swap += 1
                diff_no_swap[y1] = old - 1
                if diff_no_swap[y1] == 0:
                    nz_no_swap -= 1

                old = diff_swap[x]
                if old == 0:
                    nz_swap += 1
                diff_swap[x] = old + 1
                if diff_swap[x] == 0:
                    nz_swap -= 1

                old = diff_swap[y2]
                if old == 0:
                    nz_swap += 1
                diff_swap[y2] = old - 1
                if diff_swap[y2] == 0:
                    nz_swap -= 1

                if nz_no_swap == 0:
                    if dfs(i1, i2, k) and dfs(i1 + k, i2 + k, length - k):
                        memo[key] = True
                        return True

                if nz_swap == 0:
                    if dfs(i1, end2 - k, k) and dfs(i1 + k, i2, length - k):
                        memo[key] = True
                        return True

            memo[key] = False
            return False

        return dfs(0, 0, n)
