from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        if len(s1) != len(s2):
            return False
        if s1 == s2:
            return True

        n = len(s1)

        def build_prefix(s: str):
            pref = [[0] * 26 for _ in range(n + 1)]
            for i, ch in enumerate(s):
                row = pref[i][:]
                row[ord(ch) - 97] += 1
                pref[i + 1] = row
            return pref

        pref1 = build_prefix(s1)
        pref2 = build_prefix(s2)

        def same_counts(i1: int, i2: int, length: int) -> bool:
            a1 = pref1[i1]
            b1 = pref1[i1 + length]
            a2 = pref2[i2]
            b2 = pref2[i2 + length]
            for k in range(26):
                if b1[k] - a1[k] != b2[k] - a2[k]:
                    return False
            return True

        @lru_cache(None)
        def dfs(i: int, j: int, length: int) -> bool:
            if s1[i:i + length] == s2[j:j + length]:
                return True

            if not same_counts(i, j, length):
                return False

            for left_len in range(1, length):
                right_len = length - left_len

                # No swap
                if same_counts(i, j, left_len) and same_counts(i + left_len, j + left_len, right_len):
                    if dfs(i, j, left_len) and dfs(i + left_len, j + left_len, right_len):
                        return True

                # With swap
                if same_counts(i, j + right_len, left_len) and same_counts(i + left_len, j, right_len):
                    if dfs(i, j + right_len, left_len) and dfs(i + left_len, j, right_len):
                        return True

            return False

        return dfs(0, 0, n)
