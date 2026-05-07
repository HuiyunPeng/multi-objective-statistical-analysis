from collections import defaultdict
from typing import List


class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        word_set = set(wordList)
        if endWord not in word_set:
            return []

        letters = "abcdefghijklmnopqrstuvwxyz"
        parents = defaultdict(list)

        level = [beginWord]
        found = False
        word_set.discard(beginWord)

        while level and not found:
            next_level = []
            next_seen = set()

            for word in level:
                chars = list(word)
                for i in range(len(chars)):
                    original = chars[i]
                    for ch in letters:
                        if ch == original:
                            continue
                        chars[i] = ch
                        nxt = "".join(chars)
                        if nxt in word_set:
                            if nxt not in next_seen:
                                next_seen.add(nxt)
                                next_level.append(nxt)
                            parents[nxt].append(word)
                            if nxt == endWord:
                                found = True
                    chars[i] = original

            for w in next_level:
                word_set.discard(w)
            level = next_level

        if not found:
            return []

        res = []
        path = [endWord]

        def backtrack(word: str) -> None:
            if word == beginWord:
                res.append(path[::-1])
                return
            for prev in parents[word]:
                path.append(prev)
                backtrack(prev)
                path.pop()

        backtrack(endWord)
        return res
