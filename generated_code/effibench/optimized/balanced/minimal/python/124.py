class Solution:
    def maxPathSum(self, root):
        if root is None:
            return 0

        best = -10**18
        stack = [(root, False)]
        gains = {}

        while stack:
            node, visited = stack.pop()

            if visited:
                left_gain = gains.pop(node.left, 0) if node.left else 0
                right_gain = gains.pop(node.right, 0) if node.right else 0

                if left_gain < 0:
                    left_gain = 0
                if right_gain < 0:
                    right_gain = 0

                current_sum = node.val + left_gain + right_gain
                if current_sum > best:
                    best = current_sum

                gains[node] = node.val + (left_gain if left_gain > right_gain else right_gain)
            else:
                stack.append((node, True))
                if node.right is not None:
                    stack.append((node.right, False))
                if node.left is not None:
                    stack.append((node.left, False))

        return best
