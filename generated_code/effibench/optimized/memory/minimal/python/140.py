from functools import lru_cache

class Solution:
    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)
        lengths = sorted({len(w) for w in word_set})

        reachable = [False] * (n + 1)
        reachable[n] = True
        next_pos = [None] * n

        for i in range(n - 1, -1, -1):
            candidates = []
            for length in lengths:
                j = i + length
                if j > n:
                    break
                if reachable[j] and s[i:j] in word_set:
                    candidates.append(j)
            if candidates:
                reachable[i] = True
                next_pos[i] = candidates

        if not reachable[0]:
            return []

        @lru_cache(None)
        def build(i):
            if i == n:
                return ("",)
            res = []
            for j in next_pos[i]:
                word = s[i:j]
                for tail in build(j):
                    res.append(word if not tail else word + " " + tail)
            return tuple(res)

        ans = list(build(0))
        ans.sort(key=lambda x: (x.count(" "), x), reverse=True)
        return ans
