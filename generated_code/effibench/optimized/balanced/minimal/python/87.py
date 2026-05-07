from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        n = len(s1)
        if n != len(s2):
            return False
        if s1 == s2:
            return True

        # Prefix frequency counts for O(26) substring multiset comparison.
        pref1 = [[0] * 26 for _ in range(n + 1)]
        pref2 = [[0] * 26 for _ in range(n + 1)]

        for i, ch in enumerate(s1, 1):
            row = pref1[i]
            prev = pref1[i - 1]
            row[:] = prev
            row[ord(ch) - 97] += 1

        for i, ch in enumerate(s2, 1):
            row = pref2[i]
            prev = pref2[i - 1]
            row[:] = prev
            row[ord(ch) - 97] += 1

        def same_counts(i1: int, i2: int, length: int) -> bool:
            a = pref1[i1 + length]
            b = pref1[i1]
            c = pref2[i2 + length]
            d = pref2[i2]
            for k in range(26):
                if a[k] - b[k] != c[k] - d[k]:
                    return False
            return True

        @lru_cache(None)
        def dfs(i1: int, i2: int, length: int) -> bool:
            if s1[i1:i1 + length] == s2[i2:i2 + length]:
                return True

            if not same_counts(i1, i2, length):
                return False

            for k in range(1, length):
                # No swap case
                if same_counts(i1, i2, k) and same_counts(i1 + k, i2 + k, length - k):
                    if dfs(i1, i2, k) and dfs(i1 + k, i2 + k, length - k):
                        return True

                # Swap case
                if same_counts(i1, i2 + length - k, k) and same_counts(i1 + k, i2, length - k):
                    if dfs(i1, i2 + length - k, k) and dfs(i1 + k, i2, length - k):
                        return True

            return False

        return dfs(0, 0, n)
