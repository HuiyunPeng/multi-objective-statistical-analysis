from collections import defaultdict
from typing import List

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        word_set = set(wordList)
        if endWord not in word_set:
            return []

        word_set.discard(beginWord)
        word_len = len(beginWord)
        letters = "abcdefghijklmnopqrstuvwxyz"

        children = defaultdict(list)
        current_level = {beginWord}
        found = False

        while current_level and not found:
            for word in current_level:
                word_set.discard(word)

            next_level = set()

            for word in sorted(current_level):
                neighbors = []

                for i in range(word_len):
                    prefix = word[:i]
                    suffix = word[i + 1 :]
                    original = word[i]

                    for ch in letters:
                        if ch == original:
                            continue
                        candidate = prefix + ch + suffix
                        if candidate in word_set:
                            neighbors.append(candidate)

                neighbors.sort()
                for nei in neighbors:
                    children[word].append(nei)
                    next_level.add(nei)
                    if nei == endWord:
                        found = True

            current_level = next_level

        if not found:
            return []

        results = []
        path = [beginWord]

        def dfs(word: str) -> None:
            if word == endWord:
                results.append(path[:])
                return

            for nei in children.get(word, []):
                path.append(nei)
                dfs(nei)
                path.pop()

        dfs(beginWord)
        return results
