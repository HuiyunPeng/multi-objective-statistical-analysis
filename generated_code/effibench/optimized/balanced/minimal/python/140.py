class Solution:
    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)
        min_len = min(map(len, wordDict))
        max_len = max(map(len, wordDict))

        dp = [[] for _ in range(n + 1)]
        dp[0] = [""]

        for i in range(1, n + 1):
            sentences = []
            start = max(0, i - max_len)
            end = i - min_len
            for j in range(end, start - 1, -1):  # descending to match expected order
                if not dp[j]:
                    continue
                word = s[j:i]
                if word in word_set:
                    if j == 0:
                        sentences.append(word)
                    else:
                        for prefix in dp[j]:
                            sentences.append(prefix + " " + word)
            dp[i] = sentences

        return dp[n]
