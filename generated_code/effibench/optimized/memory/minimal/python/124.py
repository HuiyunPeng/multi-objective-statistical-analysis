class Solution:
    def maxPathSum(self, root):
        best = -10**18
        ret = 0

        # Frame: [node, state, left_gain, right_gain]
        # state 0: traverse left
        # state 1: left processed, traverse right
        # state 2: right processed, compute and return
        stack = [[root, 0, None, None]]

        while stack:
            frame = stack[-1]
            node = frame[0]
            state = frame[1]

            if state == 0:
                frame[1] = 1
                if node.left is not None:
                    stack.append([node.left, 0, None, None])
                continue

            if state == 1:
                if node.left is not None and frame[2] is None:
                    frame[2] = ret
                frame[1] = 2
                if node.right is not None:
                    stack.append([node.right, 0, None, None])
                continue

            if node.right is not None and frame[3] is None:
                frame[3] = ret

            left_gain = frame[2] if frame[2] is not None else 0
            right_gain = frame[3] if frame[3] is not None else 0

            if left_gain < 0:
                left_gain = 0
            if right_gain < 0:
                right_gain = 0

            total = node.val + left_gain + right_gain
            if total > best:
                best = total

            ret = node.val + (left_gain if left_gain > right_gain else right_gain)
            stack.pop()

        return best
