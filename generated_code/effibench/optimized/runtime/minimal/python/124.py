class Solution:
    def maxPathSum(self, root):
        max_sum = float("-inf")
        gain = {}
        stack = [(root, False)]

        while stack:
            node, visited = stack.pop()
            if node is None:
                continue

            if visited:
                left_gain = gain.get(node.left, 0)
                right_gain = gain.get(node.right, 0)

                if left_gain < 0:
                    left_gain = 0
                if right_gain < 0:
                    right_gain = 0

                current_sum = node.val + left_gain + right_gain
                if current_sum > max_sum:
                    max_sum = current_sum

                gain[node] = node.val + (left_gain if left_gain > right_gain else right_gain)
            else:
                stack.append((node, True))
                stack.append((node.right, False))
                stack.append((node.left, False))

        return max_sum
