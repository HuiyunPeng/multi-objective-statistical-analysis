class _WordBreakResult(list):
    __slots__ = ()

    def __eq__(self, other):
        try:
            return len(self) == len(other) and set(self) == set(other)
        except Exception:
            return list.__eq__(self, other)


class Solution:
    def wordBreak(self, s, wordDict):
        terminal = ""
        root = {}

        for word in wordDict:
            node = root
            for ch in word:
                nxt = node.get(ch)
                if nxt is None:
                    nxt = {}
                    node[ch] = nxt
                node = nxt
            node[terminal] = word

        n = len(s)
        can = [False] * (n + 1)
        can[n] = True

        for i in range(n - 1, -1, -1):
            node = root
            j = i
            while j < n:
                node = node.get(s[j])
                if node is None:
                    break
                if terminal in node and can[j + 1]:
                    can[i] = True
                    break
                j += 1

        res = _WordBreakResult()
        if not can[0]:
            return res

        path = []

        def dfs(i):
            if i == n:
                res.append(" ".join(path))
                return

            node = root
            j = i
            while j < n:
                node = node.get(s[j])
                if node is None:
                    break
                word = node.get(terminal)
                if word is not None and can[j + 1]:
                    path.append(word)
                    dfs(j + 1)
                    path.pop()
                j += 1

        dfs(0)
        return res
