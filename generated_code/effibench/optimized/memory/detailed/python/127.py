class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        words = set(wordList)
        if endWord not in words:
            return 0

        front = {beginWord}
        back = {endWord}
        words.discard(beginWord)
        words.discard(endWord)

        steps = 1
        alphabet = "abcdefghijklmnopqrstuvwxyz"

        while front and back:
            if len(front) > len(back):
                front, back = back, front

            next_front = set()
            for word in front:
                chars = list(word)
                for i, original in enumerate(chars):
                    for ch in alphabet:
                        if ch == original:
                            continue
                        chars[i] = ch
                        candidate = "".join(chars)

                        if candidate in back:
                            return steps + 1
                        if candidate in words:
                            words.remove(candidate)
                            next_front.add(candidate)

                    chars[i] = original

            front = next_front
            steps += 1

        return 0
