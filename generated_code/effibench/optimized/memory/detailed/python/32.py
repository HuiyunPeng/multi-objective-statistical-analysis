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
                length = left + right
                if length > best:
                    best = length
            elif right > left:
                left = right = 0

        left = right = 0
        for i in range(len(s) - 1, -1, -1):
            if s[i] == '(':
                left += 1
            else:
                right += 1
            if left == right:
                length = left + right
                if length > best:
                    best = length
            elif left > right:
                left = right = 0

        return best
