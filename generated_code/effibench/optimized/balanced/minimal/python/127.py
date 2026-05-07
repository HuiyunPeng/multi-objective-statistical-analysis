class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        words = set(wordList)
        if endWord not in words:
            return 0

        begin_front = {beginWord}
        end_front = {endWord}
        words.discard(beginWord)
        words.discard(endWord)

        steps = 1
        alphabet = "abcdefghijklmnopqrstuvwxyz"

        while begin_front and end_front:
            if len(begin_front) > len(end_front):
                begin_front, end_front = end_front, begin_front

            next_front = set()
            for word in begin_front:
                chars = list(word)
                for i, original in enumerate(chars):
                    for ch in alphabet:
                        if ch == original:
                            continue
                        chars[i] = ch
                        nxt = "".join(chars)

                        if nxt in end_front:
                            return steps + 1
                        if nxt in words:
                            next_front.add(nxt)
                            words.remove(nxt)

                    chars[i] = original

            begin_front = next_front
            steps += 1

        return 0
