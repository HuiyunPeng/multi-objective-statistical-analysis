class Solution:
    def alienOrder(self, words):
        present_mask = 0
        for word in words:
            for ch in word:
                present_mask |= 1 << (ord(ch) - 97)

        adj = [0] * 26
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
            if (adj[u] & bit) == 0:
                adj[u] |= bit
                indegree[v] += 1

        queue = []
        for i in range(26):
            if (present_mask >> i) & 1 and indegree[i] == 0:
                queue.append(i)

        res = []
        head = 0

        while head < len(queue):
            u = queue[head]
            head += 1
            res.append(chr(u + 97))

            neighbors = adj[u]
            while neighbors:
                lsb = neighbors & -neighbors
                v = lsb.bit_length() - 1
                indegree[v] -= 1
                if indegree[v] == 0:
                    queue.append(v)
                neighbors ^= lsb

        if len(res) != present_mask.bit_count():
            return ""

        return "".join(res)
