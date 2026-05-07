class Solution:
    def maxPathSum(self, root):
        best = -10**18
        ret = 0
        stack = [[root, 0, 0, 0]]  # node, state, left_gain, right_gain

        while stack:
            frame = stack[-1]
            node = frame[0]
            state = frame[1]

            if state == 0:
                frame[1] = 1
                if node.left is not None:
                    stack.append([node.left, 0, 0, 0])
                else:
                    frame[2] = 0

            elif state == 1:
                if node.left is not None:
                    frame[2] = ret
                frame[1] = 2
                if node.right is not None:
                    stack.append([node.right, 0, 0, 0])
                else:
                    frame[3] = 0

            else:
                if node.right is not None:
                    frame[3] = ret

                left_gain = frame[2]
                right_gain = frame[3]

                if left_gain < 0:
                    left_gain = 0
                if right_gain < 0:
                    right_gain = 0

                path_sum = node.val + left_gain + right_gain
                if path_sum > best:
                    best = path_sum

                ret = node.val + (left_gain if left_gain > right_gain else right_gain)
                stack.pop()

        return best
