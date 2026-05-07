class Solution:
    def findLadders(self, beginWord, endWord, wordList):
        word_set = set(wordList)
        if endWord not in word_set:
            return []

        word_set.discard(beginWord)
        parents = {}
        current_level = [beginWord]
        letters = "abcdefghijklmnopqrstuvwxyz"
        found = False

        while current_level and not found:
            next_level = set()

            for word in current_level:
                chars = list(word)
                for i, original in enumerate(chars):
                    for ch in letters:
                        if ch == original:
                            continue
                        chars[i] = ch
                        nxt = "".join(chars)
                        if nxt in word_set:
                            if nxt not in next_level:
                                next_level.add(nxt)
                                parents[nxt] = [word]
                            else:
                                parents[nxt].append(word)

                            if nxt == endWord:
                                found = True
                    chars[i] = original

            word_set -= next_level
            current_level = sorted(next_level)

        if not found:
            return []

        result = []
        path = [endWord]

        def backtrack(word):
            if word == beginWord:
                result.append(path[::-1])
                return
            for prev in parents[word]:
                path.append(prev)
                backtrack(prev)
                path.pop()

        backtrack(endWord)
        return result
