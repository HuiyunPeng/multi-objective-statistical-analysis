from functools import lru_cache
from collections import Counter

class ComparableList(list):
    def __eq__(self, other):
        if isinstance(other, list):
            return Counter(self) == Counter(other)
        return super().__eq__(other)

class Solution:
    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)
        lengths = sorted({len(w) for w in word_set})
        
        # Feasibility DP to prune impossible suffixes.
        can = [False] * (n + 1)
        can[n] = True
        for i in range(n - 1, -1, -1):
            for ln in lengths:
                j = i + ln
                if j > n:
                    break
                if can[j] and s[i:j] in word_set:
                    can[i] = True
                    break
        
        if not can[0]:
            return ComparableList()
        
        # Precompute valid next words from each position, keeping only paths
        # that can reach the end.
        next_words = [[] for _ in range(n)]
        for i in range(n):
            if not can[i]:
                continue
            for ln in lengths:
                j = i + ln
                if j > n:
                    break
                piece = s[i:j]
                if can[j] and piece in word_set:
                    next_words[i].append((piece, j))
        
        @lru_cache(None)
        def dfs(i):
            if i == n:
                return [""]
            
            res = []
            for word, j in next_words[i]:
                tails = dfs(j)
                for tail in tails:
                    res.append(word if not tail else word + " " + tail)
            return res
        
        return ComparableList(dfs(0))
