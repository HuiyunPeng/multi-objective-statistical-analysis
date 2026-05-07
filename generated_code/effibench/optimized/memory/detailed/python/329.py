class Solution:
    def longestIncreasingPath(self, matrix):
        m = len(matrix)
        n = len(matrix[0])

        outdeg = bytearray(m * n)

        # Compute outdegree: number of neighbors with a greater value.
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
                outdeg[base + j] = d

        # Start from local maxima (outdegree 0).
        q = [idx for idx, d in enumerate(outdeg) if d == 0]
        ans = 0

        while q:
            ans += 1
            nq = []
            for idx in q:
                i, j = divmod(idx, n)
                v = matrix[i][j]

                ni = i - 1
                if ni >= 0 and matrix[ni][j] < v:
                    k = ni * n + j
                    outdeg[k] -= 1
                    if outdeg[k] == 0:
                        nq.append(k)

                ni = i + 1
                if ni < m and matrix[ni][j] < v:
                    k = ni * n + j
                    outdeg[k] -= 1
                    if outdeg[k] == 0:
                        nq.append(k)

                nj = j - 1
                if nj >= 0 and matrix[i][nj] < v:
                    k = i * n + nj
                    outdeg[k] -= 1
                    if outdeg[k] == 0:
                        nq.append(k)

                nj = j + 1
                if nj < n and matrix[i][nj] < v:
                    k = i * n + nj
                    outdeg[k] -= 1
                    if outdeg[k] == 0:
                        nq.append(k)

            q = nq

        return ans
