class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        word_set = set(wordList)
        if endWord not in word_set:
            return 0

        begin_front = {beginWord}
        end_front = {endWord}
        word_set.discard(beginWord)

        steps = 1
        letters = "abcdefghijklmnopqrstuvwxyz"
        word_len = len(beginWord)

        while begin_front and end_front:
            if len(begin_front) > len(end_front):
                begin_front, end_front = end_front, begin_front

            next_front = set()

            for word in begin_front:
                for i in range(word_len):
                    original = word[i]
                    prefix = word[:i]
                    suffix = word[i + 1:]

                    for ch in letters:
                        if ch == original:
                            continue
                        candidate = prefix + ch + suffix

                        if candidate in end_front:
                            return steps + 1

                        if candidate in word_set:
                            word_set.remove(candidate)
                            next_front.add(candidate)

            begin_front = next_front
            steps += 1

        return 0
