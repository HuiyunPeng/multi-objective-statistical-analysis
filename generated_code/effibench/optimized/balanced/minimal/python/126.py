from typing import List
from collections import defaultdict

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        word_set = set(wordList)
        if endWord not in word_set:
            return []

        available = set(word_set)
        available.discard(beginWord)

        children = defaultdict(list)
        level = [beginWord]
        found = False
        letters = "abcdefghijklmnopqrstuvwxyz"
        word_len = len(beginWord)

        while level and not found:
            next_level = []
            visited_this_level = set()

            for word in level:
                word_chars = list(word)
                for i in range(word_len):
                    original = word_chars[i]
                    for ch in letters:
                        if ch == original:
                            continue
                        word_chars[i] = ch
                        nxt = "".join(word_chars)
                        if nxt in available:
                            children[word].append(nxt)
                            if nxt not in visited_this_level:
                                visited_this_level.add(nxt)
                                next_level.append(nxt)
                            if nxt == endWord:
                                found = True
                    word_chars[i] = original

            available.difference_update(visited_this_level)
            level = next_level

        if not found:
            return []

        result = []
        path = [beginWord]

        def dfs(word: str) -> None:
            if word == endWord:
                result.append(path[:])
                return
            for nxt in children.get(word, ()):
                path.append(nxt)
                dfs(nxt)
                path.pop()

        dfs(beginWord)
        return result
