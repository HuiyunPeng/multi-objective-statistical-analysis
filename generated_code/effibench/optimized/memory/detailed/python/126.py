from typing import List
from collections import defaultdict

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        remaining = set(wordList)
        if endWord not in remaining:
            return []

        parents = defaultdict(list)
        current = [beginWord]
        letters = "abcdefghijklmnopqrstuvwxyz"
        found = False
        word_len = len(beginWord)

        while current and not found:
            for word in current:
                remaining.discard(word)

            next_level = []
            next_seen = set()

            for word in current:
                chars = list(word)
                for i in range(word_len):
                    original = chars[i]
                    for ch in letters:
                        if ch == original:
                            continue
                        chars[i] = ch
                        candidate = "".join(chars)
                        if candidate in remaining:
                            parents[candidate].append(word)
                            if candidate not in next_seen:
                                next_seen.add(candidate)
                                next_level.append(candidate)
                            if candidate == endWord:
                                found = True
                    chars[i] = original

            current = next_level

        if not found:
            return []

        result = []
        path = [endWord]

        def build(word: str) -> None:
            if word == beginWord:
                result.append(path[::-1])
                return
            for prev in parents[word]:
                path.append(prev)
                build(prev)
                path.pop()

        build(endWord)
        return result
