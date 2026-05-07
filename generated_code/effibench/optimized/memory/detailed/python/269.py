from typing import List

class Solution:
    def alienOrder(self, words: List[str]) -> str:
        adj = [0] * 26
        indeg = [0] * 26
        present_mask = 0

        for word in words:
            for ch in word:
                present_mask |= 1 << (ord(ch) - 97)

        for i in range(len(words) - 1):
            a = words[i]
            b = words[i + 1]
            limit = min(len(a), len(b))
            j = 0

            while j < limit and a[j] == b[j]:
                j += 1

            if j == limit:
                if len(a) > len(b):
                    return ""
                continue

            u = ord(a[j]) - 97
            v = ord(b[j]) - 97
            bit = 1 << v
            if (adj[u] & bit) == 0:
                adj[u] |= bit
                indeg[v] += 1

        zeros = []
        for i in range(26):
            if ((present_mask >> i) & 1) and indeg[i] == 0:
                zeros.append(i)

        res = []
        head = 0

        while head < len(zeros):
            u = zeros[head]
            head += 1
            res.append(chr(u + 97))

            mask = adj[u]
            while mask:
                lsb = mask & -mask
                v = lsb.bit_length() - 1
                indeg[v] -= 1
                if indeg[v] == 0:
                    zeros.append(v)
                mask ^= lsb

        if len(res) != present_mask.bit_count():
            return ""

        return "".join(res)
