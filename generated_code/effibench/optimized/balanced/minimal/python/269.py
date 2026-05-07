from collections import deque

class Solution:
    def alienOrder(self, words):
        indegree = {}
        graph = {}

        for word in words:
            for ch in word:
                if ch not in indegree:
                    indegree[ch] = 0
                    graph[ch] = set()

        for i in range(len(words) - 1):
            w1, w2 = words[i], words[i + 1]
            min_len = min(len(w1), len(w2))
            j = 0

            while j < min_len and w1[j] == w2[j]:
                j += 1

            if j == min_len:
                if len(w1) > len(w2):
                    return ""
                continue

            a, b = w1[j], w2[j]
            if b not in graph[a]:
                graph[a].add(b)
                indegree[b] += 1

        q = deque([ch for ch in indegree if indegree[ch] == 0])
        order = []

        while q:
            ch = q.popleft()
            order.append(ch)
            for nei in graph[ch]:
                indegree[nei] -= 1
                if indegree[nei] == 0:
                    q.append(nei)

        return "".join(order) if len(order) == len(indegree) else ""
