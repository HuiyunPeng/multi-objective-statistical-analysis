from typing import List

class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        total = m * n
        outdegree = bytearray(total)
        queue = []

        for i in range(m):
            row = matrix[i]
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
                idx = i * n + j
                outdegree[idx] = deg
                if deg == 0:
                    queue.append(idx)

        length = 0
        while queue:
            length += 1
            next_queue = []
            for idx in queue:
                i, j = divmod(idx, n)
                v = matrix[i][j]

                if i > 0 and matrix[i - 1][j] < v:
                    nidx = idx - n
                    outdegree[nidx] -= 1
                    if outdegree[nidx] == 0:
                        next_queue.append(nidx)

                if i + 1 < m and matrix[i + 1][j] < v:
                    nidx = idx + n
                    outdegree[nidx] -= 1
                    if outdegree[nidx] == 0:
                        next_queue.append(nidx)

                if j > 0 and matrix[i][j - 1] < v:
                    nidx = idx - 1
                    outdegree[nidx] -= 1
                    if outdegree[nidx] == 0:
                        next_queue.append(nidx)

                if j + 1 < n and matrix[i][j + 1] < v:
                    nidx = idx + 1
                    outdegree[nidx] -= 1
                    if outdegree[nidx] == 0:
                        next_queue.append(nidx)

            queue = next_queue

        return length
