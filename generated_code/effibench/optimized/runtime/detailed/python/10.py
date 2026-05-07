class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        tokens = []
        i = 0
        n = len(p)
        while i < n:
            ch = p[i]
            if i + 1 < n and p[i + 1] == '*':
                tokens.append((ch, True))
                i += 2
            else:
                tokens.append((ch, False))
                i += 1

        t = len(tokens)

        # dp[j] = whether empty string matches tokens[j:]
        dp = [False] * (t + 1)
        dp[t] = True
        for j in range(t - 1, -1, -1):
            if tokens[j][1]:
                dp[j] = dp[j + 1]

        for idx in range(len(s) - 1, -1, -1):
            c = s[idx]
            new = [False] * (t + 1)
            for j in range(t - 1, -1, -1):
                ch, starred = tokens[j]
                first = ch == '.' or ch == c
                if starred:
                    new[j] = new[j + 1] or (first and dp[j])
                else:
                    new[j] = first and dp[j + 1]
            dp = new

        return dp[0]
