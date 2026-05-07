import sys

class Solution:
    def maxPathSum(self, root):
        sys.setrecursionlimit(100000)

        best = -10**18

        def dfs(node):
            nonlocal best
            if node is None:
                return 0

            left = dfs(node.left)
            if left < 0:
                left = 0

            right = dfs(node.right)
            if right < 0:
                right = 0

            total = node.val + left + right
            if total > best:
                best = total

            return node.val + (left if left > right else right)

        dfs(root)
        return best
