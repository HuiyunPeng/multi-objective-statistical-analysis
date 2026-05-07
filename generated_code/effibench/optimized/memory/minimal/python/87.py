from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        if s1 == s2:
            return True

        n = len(s1)
        if n != len(s2):
            return False

        # Prefix frequency counts for fast anagram checks on any substring.
        p1 = [[0] * (n + 1) for _ in range(26)]
        p2 = [[0] * (n + 1) for _ in range(26)]

        for i in range(n):
            c1 = ord(s1[i]) - 97
            c2 = ord(s2[i]) - 97
            for ch in range(26):
                p1[ch][i + 1] = p1[ch][i]
                p2[ch][i + 1] = p2[ch][i]
            p1[c1][i + 1] += 1
            p2[c2][i + 1] += 1

        def same_count(i1: int, i2: int, length: int) -> bool:
            end1 = i1 + length
            end2 = i2 + length
            for ch in range(26):
                if p1[ch][end1] - p1[ch][i1] != p2[ch][end2] - p2[ch][i2]:
                    return False
            return True

        def same_string(i1: int, i2: int, length: int) -> bool:
            for k in range(length):
                if s1[i1 + k] != s2[i2 + k]:
                    return False
            return True

        @lru_cache(None)
        def dfs(i1: int, i2: int, length: int) -> bool:
            if same_string(i1, i2, length):
                return True
            if not same_count(i1, i2, length):
                return False

            for left_len in range(1, length):
                right_len = length - left_len

                # No swap
                if dfs(i1, i2, left_len) and dfs(i1 + left_len, i2 + left_len, right_len):
                    return True

                # Swap
                if dfs(i1, i2 + right_len, left_len) and dfs(i1 + left_len, i2, right_len):
                    return True

            return False

        return dfs(0, 0, n)
