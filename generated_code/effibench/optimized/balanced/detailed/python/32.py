class Solution:
    def longestValidParentheses(self, s: str) -> int:
        best = 0

        open_count = close_count = 0
        for ch in s:
            if ch == '(':
                open_count += 1
            else:
                close_count += 1

            if open_count == close_count:
                length = close_count * 2
                if length > best:
                    best = length
            elif close_count > open_count:
                open_count = close_count = 0

        open_count = close_count = 0
        for i in range(len(s) - 1, -1, -1):
            if s[i] == '(':
                open_count += 1
            else:
                close_count += 1

            if open_count == close_count:
                length = open_count * 2
                if length > best:
                    best = length
            elif open_count > close_count:
                open_count = close_count = 0

        return best
