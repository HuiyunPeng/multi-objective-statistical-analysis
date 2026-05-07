class Solution:
    def alienOrder(self, words):
        present = [False] * 26
        for word in words:
            for ch in word:
                present[ord(ch) - 97] = True

        outmask = [0] * 26
        indegree = [0] * 26

        for i in range(len(words) - 1):
            a = words[i]
            b = words[i + 1]
            m = min(len(a), len(b))

            j = 0
            while j < m and a[j] == b[j]:
                j += 1

            if j == m:
                if len(a) > len(b):
                    return ""
                continue

            u = ord(a[j]) - 97
            v = ord(b[j]) - 97
            bit = 1 << v
            if not (outmask[u] & bit):
                outmask[u] |= bit
                indegree[v] += 1

        queue = [i for i in range(26) if present[i] and indegree[i] == 0]
        res = []
        head = 0

        while head < len(queue):
            u = queue[head]
            head += 1
            res.append(chr(u + 97))

            mask = outmask[u]
            while mask:
                bit = mask & -mask
                v = bit.bit_length() - 1
                indegree[v] -= 1
                if indegree[v] == 0:
                    queue.append(v)
                mask ^= bit

        total = sum(present)
        return "".join(res) if len(res) == total else ""
