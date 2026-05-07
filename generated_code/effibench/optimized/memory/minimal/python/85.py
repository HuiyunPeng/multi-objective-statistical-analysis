class Solution:
    def maximalRectangle(self, matrix):
        if not matrix or not matrix[0]:
            return 0

        cols = len(matrix[0])
        heights = [0] * (cols + 1)  # extra sentinel 0 to flush stack
        best = 0

        for row in matrix:
            for j in range(cols):
                heights[j] = heights[j] + 1 if row[j] == "1" else 0

            stack = [-1]
            for i in range(cols + 1):
                while heights[i] < heights[stack[-1]] if stack[-1] != -1 else False:
                    h = heights[stack.pop()]
                    w = i - stack[-1] - 1
                    area = h * w
                    if area > best:
                        best = area
                stack.append(i)

        return best
