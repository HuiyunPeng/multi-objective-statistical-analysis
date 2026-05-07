from collections import deque
from typing import List

class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        outdegree = [[0] * n for _ in range(m)]
        q = deque()

        for i in range(m):
            row = matrix[i]
            for j in range(n):
                v = row[j]
                deg = 0
                if i > 0 and matrix[i - 1][j] > v:
                    deg += 1
                if i + 1 < m and matrix[i + 1][j] > v:
                    deg += 1
                if j > 0 and matrix[i][j - 1] > v:
                    deg += 1
                if j + 1 < n and matrix[i][j + 1] > v:
                    deg += 1
                outdegree[i][j] = deg
                if deg == 0:
                    q.append((i, j))

        length = 0
        while q:
            length += 1
            for _ in range(len(q)):
                i, j = q.popleft()
                v = matrix[i][j]

                if i > 0 and matrix[i - 1][j] < v:
                    outdegree[i - 1][j] -= 1
                    if outdegree[i - 1][j] == 0:
                        q.append((i - 1, j))

                if i + 1 < m and matrix[i + 1][j] < v:
                    outdegree[i + 1][j] -= 1
                    if outdegree[i + 1][j] == 0:
                        q.append((i + 1, j))

                if j > 0 and matrix[i][j - 1] < v:
                    outdegree[i][j - 1] -= 1
                    if outdegree[i][j - 1] == 0:
                        q.append((i, j - 1))

                if j + 1 < n and matrix[i][j + 1] < v:
                    outdegree[i][j + 1] -= 1
                    if outdegree[i][j + 1] == 0:
                        q.append((i, j + 1))

        return length
