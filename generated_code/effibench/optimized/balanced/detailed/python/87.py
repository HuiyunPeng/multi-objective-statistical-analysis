from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        if s1 == s2:
            return True

        n = len(s1)
        if n != len(s2):
            return False

        # Quick global character-count check.
        diff = [0] * 26
        for a, b in zip(s1, s2):
            diff[ord(a) - 97] += 1
            diff[ord(b) - 97] -= 1
        if any(diff):
            return False

        # Prefix counts for O(26) substring multiset comparison.
        pref1 = [[0] * (n + 1) for _ in range(26)]
        pref2 = [[0] * (n + 1) for _ in range(26)]

        for c in range(26):
            ch = chr(97 + c)

            cnt = 0
            row = pref1[c]
            for i, x in enumerate(s1, 1):
                if x == ch:
                    cnt += 1
                row[i] = cnt

            cnt = 0
            row = pref2[c]
            for i, x in enumerate(s2, 1):
                if x == ch:
                    cnt += 1
                row[i] = cnt

        @lru_cache(None)
        def same_counts(i: int, j: int, length: int) -> bool:
            end1 = i + length
            end2 = j + length
            for c in range(26):
                if pref1[c][end1] - pref1[c][i] != pref2[c][end2] - pref2[c][j]:
                    return False
            return True

        def same_string(i: int, j: int, length: int) -> bool:
            for k in range(length):
                if s1[i + k] != s2[j + k]:
                    return False
            return True

        @lru_cache(None)
        def dfs(i: int, j: int, length: int) -> bool:
            if length == 1:
                return s1[i] == s2[j]

            if not same_counts(i, j, length):
                return False

            if same_string(i, j, length):
                return True

            for left in range(1, length):
                # No swap case
                if same_counts(i, j, left):
                    if dfs(i, j, left) and dfs(i + left, j + left, length - left):
                        return True

                # Swap case
                if same_counts(i, j + length - left, left):
                    if dfs(i, j + length - left, left) and dfs(i + left, j, length - left):
                        return True

            return False

        return dfs(0, 0, n)
