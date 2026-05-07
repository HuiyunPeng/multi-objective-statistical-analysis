from functools import lru_cache
from typing import List

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        word_set = set(wordDict)
        lengths = sorted({len(w) for w in word_set})
        n = len(s)

        can = [False] * (n + 1)
        can[n] = True

        for i in range(n - 1, -1, -1):
            for length in lengths:
                j = i + length
                if j > n:
                    break
                if can[j] and s[i:j] in word_set:
                    can[i] = True
                    break

        if not can[0]:
            return []

        next_words = [[] for _ in range(n)]
        for i in range(n):
            if not can[i]:
                continue
            for length in lengths:
                j = i + length
                if j > n:
                    break
                if can[j]:
                    word = s[i:j]
                    if word in word_set:
                        next_words[i].append((j, word))

        @lru_cache(None)
        def dfs(i: int) -> List[str]:
            if i == n:
                return [""]
            res = []
            for j, word in next_words[i]:
                for tail in dfs(j):
                    res.append(word if not tail else word + " " + tail)
            return res

        ans = dfs(0)
        ans.sort(key=lambda sentence: (sentence.count(" ") + 1, sentence), reverse=True)
        return ans
