class Solution:
    def longestValidParentheses(self, s: str) -> int:
        best = 0
        left = right = 0

        for ch in s:
            if ch == '(':
                left += 1
            else:
                right += 1

            if left == right:
                best = max(best, 2 * right)
            elif right > left:
                left = right = 0

        left = right = 0
        for ch in reversed(s):
            if ch == '(':
                left += 1
            else:
                right += 1

            if left == right:
                best = max(best, 2 * left)
            elif left > right:
                left = right = 0

        return best
