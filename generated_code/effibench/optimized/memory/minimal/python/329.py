class Solution:
    def longestIncreasingPath(self, matrix):
        m = len(matrix)
        n = len(matrix[0])

        outdeg = bytearray(m * n)
        current = []

        for i in range(m):
            row = matrix[i]
            base = i * n
            for j in range(n):
                v = row[j]
                d = 0
                if i > 0 and matrix[i - 1][j] > v:
                    d += 1
                if i + 1 < m and matrix[i + 1][j] > v:
                    d += 1
                if j > 0 and row[j - 1] > v:
                    d += 1
                if j + 1 < n and row[j + 1] > v:
                    d += 1

                idx = base + j
                outdeg[idx] = d
                if d == 0:
                    current.append(idx)

        length = 0
        nxt = []

        while current:
            length += 1
            nxt.clear()

            for idx in current:
                i, j = divmod(idx, n)
                v = matrix[i][j]

                if i > 0 and matrix[i - 1][j] < v:
                    ni = idx - n
                    outdeg[ni] -= 1
                    if outdeg[ni] == 0:
                        nxt.append(ni)

                if i + 1 < m and matrix[i + 1][j] < v:
                    ni = idx + n
                    outdeg[ni] -= 1
                    if outdeg[ni] == 0:
                        nxt.append(ni)

                if j > 0 and matrix[i][j - 1] < v:
                    ni = idx - 1
                    outdeg[ni] -= 1
                    if outdeg[ni] == 0:
                        nxt.append(ni)

                if j + 1 < n and matrix[i][j + 1] < v:
                    ni = idx + 1
                    outdeg[ni] -= 1
                    if outdeg[ni] == 0:
                        nxt.append(ni)

            current, nxt = nxt, current

        return length
