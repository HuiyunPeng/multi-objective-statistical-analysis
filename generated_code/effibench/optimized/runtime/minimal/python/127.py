class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        word_set = set(wordList)
        if endWord not in word_set:
            return 0

        alphabet = "abcdefghijklmnopqrstuvwxyz"

        front = {beginWord}
        back = {endWord}

        dist_front = {beginWord: 1}
        dist_back = {endWord: 1}

        unvisited = set(wordList)
        unvisited.discard(beginWord)
        unvisited.discard(endWord)

        while front and back:
            if len(front) > len(back):
                front, back = back, front
                dist_front, dist_back = dist_back, dist_front

            next_front = set()

            for word in front:
                current_dist = dist_front[word]
                chars = list(word)

                for i, original_char in enumerate(chars):
                    for ch in alphabet:
                        if ch == original_char:
                            continue

                        chars[i] = ch
                        neighbor = "".join(chars)

                        if neighbor in dist_back:
                            return current_dist + dist_back[neighbor]

                        if neighbor in unvisited:
                            unvisited.remove(neighbor)
                            dist_front[neighbor] = current_dist + 1
                            next_front.add(neighbor)

                    chars[i] = original_char

            front = next_front

        return 0
