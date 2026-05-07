from collections import defaultdict

class Solution:
    def findLadders(self, beginWord, endWord, wordList):
        word_set = set(wordList)
        if endWord not in word_set:
            return []

        L = len(beginWord)
        children = defaultdict(list)

        current_level = [beginWord]
        found = False

        while current_level and not found:
            current_set = set(current_level)
            word_set -= current_set

            next_level = []
            next_level_seen = set()

            for word in current_level:
                word_chars = list(word)
                for i in range(L):
                    original = word_chars[i]
                    for c in "abcdefghijklmnopqrstuvwxyz":
                        if c == original:
                            continue
                        word_chars[i] = c
                        nxt = "".join(word_chars)
                        if nxt in word_set:
                            children[word].append(nxt)
                            if nxt not in next_level_seen:
                                next_level_seen.add(nxt)
                                next_level.append(nxt)
                            if nxt == endWord:
                                found = True
                    word_chars[i] = original

            current_level = next_level

        if not found:
            return []

        res = []
        path = [beginWord]

        def dfs(word):
            if word == endWord:
                res.append(path[:])
                return
            for nxt in children[word]:
                path.append(nxt)
                dfs(nxt)
                path.pop()

        dfs(beginWord)
        return res
