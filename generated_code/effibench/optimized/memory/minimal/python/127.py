class Solution:
    def ladderLength(self, beginWord, endWord, wordList):
        remaining = set(wordList)
        if endWord not in remaining:
            return 0

        begin_front = {beginWord}
        end_front = {endWord}
        remaining.discard(beginWord)
        remaining.discard(endWord)

        letters = "abcdefghijklmnopqrstuvwxyz"
        steps = 1

        while begin_front and end_front:
            if len(begin_front) > len(end_front):
                begin_front, end_front = end_front, begin_front

            next_front = set()

            for word in begin_front:
                for i, original_char in enumerate(word):
                    prefix = word[:i]
                    suffix = word[i + 1:]

                    for ch in letters:
                        if ch == original_char:
                            continue
                        candidate = prefix + ch + suffix

                        if candidate in end_front:
                            return steps + 1

                        if candidate in remaining:
                            remaining.remove(candidate)
                            next_front.add(candidate)

            begin_front = next_front
            steps += 1

        return 0
