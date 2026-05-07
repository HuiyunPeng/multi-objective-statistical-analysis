from collections import deque
from typing import List

class Solution:
    def alienOrder(self, words: List[str]) -> str:
        # Initialize graph with every unique character.
        graph = {c: set() for word in words for c in word}
        indegree = {c: 0 for c in graph}

        # Build ordering constraints from adjacent words.
        for i in range(len(words) - 1):
            w1, w2 = words[i], words[i + 1]

            # Invalid if a longer word comes before its exact prefix.
            min_len = min(len(w1), len(w2))
            if len(w1) > len(w2) and w1[:min_len] == w2[:min_len]:
                return ""

            for j in range(min_len):
                if w1[j] != w2[j]:
                    if w2[j] not in graph[w1[j]]:
                        graph[w1[j]].add(w2[j])
                        indegree[w2[j]] += 1
                    break

        # Topological sort (Kahn's algorithm).
        queue = deque([c for c in graph if indegree[c] == 0])
        order = []

        while queue:
            c = queue.popleft()
            order.append(c)
            for nei in graph[c]:
                indegree[nei] -= 1
                if indegree[nei] == 0:
                    queue.append(nei)

        return "".join(order) if len(order) == len(graph) else ""
