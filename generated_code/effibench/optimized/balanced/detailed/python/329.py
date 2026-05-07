from collections import deque
from typing import List

class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m = len(matrix)
        n = len(matrix[0])
        total = m * n

        # outdegree[cell] = number of neighbors with a strictly larger value
        outdegree = bytearray(total)
        q = deque()

        for i in range(m):
            row = matrix[i]
            base = i * n
            for j in range(n):
                v = row[j]
                deg = 0
                if i > 0 and matrix[i - 1][j] > v:
                    deg += 1
                if i + 1 < m and matrix[i + 1][j] > v:
                    deg += 1
                if j > 0 and row[j - 1] > v:
                    deg += 1
                if j + 1 < n and row[j + 1] > v:
                    deg += 1
                idx = base + j
                outdegree[idx] = deg
                if deg == 0:
                    q.append(idx)

        # Topological layering from local maxima downward.
        # Number of layers equals the longest increasing path length.
        layers = 0
        while q:
            layers += 1
            for _ in range(len(q)):
                idx = q.popleft()
                i, j = divmod(idx, n)
                v = matrix[i][j]

                if i > 0 and matrix[i - 1][j] < v:
                    k = idx - n
                    outdegree[k] -= 1
                    if outdegree[k] == 0:
                        q.append(k)
                if i + 1 < m and matrix[i + 1][j] < v:
                    k = idx + n
                    outdegree[k] -= 1
                    if outdegree[k] == 0:
                        q.append(k)
                if j > 0 and matrix[i][j - 1] < v:
                    k = idx - 1
                    outdegree[k] -= 1
                    if outdegree[k] == 0:
                        q.append(k)
                if j + 1 < n and matrix[i][j + 1] < v:
                    k = idx + 1
                    outdegree[k] -= 1
                    if outdegree[k] == 0:
                        q.append(k)

        return layers
