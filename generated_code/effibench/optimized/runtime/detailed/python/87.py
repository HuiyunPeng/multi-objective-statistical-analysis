from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        n = len(s1)
        if s1 == s2:
            return True
        if n != len(s2):
            return False

        pref1 = [[0] * 26 for _ in range(n + 1)]
        pref2 = [[0] * 26 for _ in range(n + 1)]

        for i in range(n):
            row1 = pref1[i + 1]
            prev1 = pref1[i]
            row2 = pref2[i + 1]
            prev2 = pref2[i]

            for c in range(26):
                row1[c] = prev1[c]
                row2[c] = prev2[c]

            row1[ord(s1[i]) - 97] += 1
            row2[ord(s2[i]) - 97] += 1

        def same_counts(i: int, j: int, length: int) -> bool:
            a = pref1[i]
            b = pref1[i + length]
            c = pref2[j]
            d = pref2[j + length]
            for k in range(26):
                if b[k] - a[k] != d[k] - c[k]:
                    return False
            return True

        def same_substring(i: int, j: int, length: int) -> bool:
            for k in range(length):
                if s1[i + k] != s2[j + k]:
                    return False
            return True

        @lru_cache(None)
        def dfs(i: int, j: int, length: int) -> bool:
            if length == 1:
                return s1[i] == s2[j]

            if same_substring(i, j, length):
                return True

            if not same_counts(i, j, length):
                return False

            for left_len in range(1, length):
                right_len = length - left_len

                if same_counts(i, j, left_len) and same_counts(i + left_len, j + left_len, right_len):
                    if dfs(i, j, left_len) and dfs(i + left_len, j + left_len, right_len):
                        return True

                if same_counts(i, j + right_len, left_len) and same_counts(i + left_len, j, right_len):
                    if dfs(i, j + right_len, left_len) and dfs(i + left_len, j, right_len):
                        return True

            return False

        return dfs(0, 0, n)
