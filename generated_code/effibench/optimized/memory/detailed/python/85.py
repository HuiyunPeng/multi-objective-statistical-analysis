class Solution:
    def maximalRectangle(self, matrix):
        if not matrix or not matrix[0]:
            return 0

        cols = len(matrix[0])
        heights = [0] * cols
        stack = [0] * (cols + 1)  # reused monotonic stack storage
        best = 0

        for row in matrix:
            for j in range(cols):
                if row[j] == "1":
                    heights[j] += 1
                else:
                    heights[j] = 0

            top = -1
            for j in range(cols + 1):
                curr = heights[j] if j < cols else 0
                while top >= 0 and curr < heights[stack[top]]:
                    h = heights[stack[top]]
                    top -= 1
                    left = stack[top] if top >= 0 else -1
                    area = h * (j - left - 1)
                    if area > best:
                        best = area
                top += 1
                stack[top] = j

        return best
