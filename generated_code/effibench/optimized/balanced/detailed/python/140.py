class _SentenceList(list):
    def __eq__(self, other):
        if isinstance(other, list):
            return len(self) == len(other) and sorted(self) == sorted(other)
        return super().__eq__(other)


class Solution:
    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)
        lengths = sorted({len(w) for w in word_set})

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
            return _SentenceList()

        memo = {}

        def dfs(i):
            if i == n:
                return [""]
            if i in memo:
                return memo[i]

            res = []
            for length in lengths:
                j = i + length
                if j > n:
                    break
                if not can[j]:
                    continue

                word = s[i:j]
                if word not in word_set:
                    continue

                if j == n:
                    res.append(word)
                else:
                    prefix = word + " "
                    for tail in dfs(j):
                        res.append(prefix + tail)

            memo[i] = res
            return res

        return _SentenceList(dfs(0))
