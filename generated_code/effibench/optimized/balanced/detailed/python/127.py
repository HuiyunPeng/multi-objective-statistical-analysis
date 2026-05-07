class Solution:
    def ladderLength(self, beginWord, endWord, wordList):
        word_set = set(wordList)
        if endWord not in word_set:
            return 0

        front = {beginWord}
        back = {endWord}
        word_set.discard(beginWord)
        word_set.discard(endWord)

        steps = 1
        letters = "abcdefghijklmnopqrstuvwxyz"
        word_len = len(beginWord)

        while front and back:
            if len(front) > len(back):
                front, back = back, front

            next_front = set()

            for word in front:
                chars = list(word)
                for i in range(word_len):
                    original = chars[i]
                    for ch in letters:
                        if ch == original:
                            continue
                        chars[i] = ch
                        nxt = ''.join(chars)

                        if nxt in back:
                            return steps + 1
                        if nxt in word_set:
                            word_set.remove(nxt)
                            next_front.add(nxt)

                    chars[i] = original

            front = next_front
            steps += 1

        return 0
