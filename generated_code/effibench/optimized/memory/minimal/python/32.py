class Solution:
    def longestValidParentheses(self, s: str) -> int:
        longest = 0
        
        left = right = 0
        for ch in s:
            if ch == '(':
                left += 1
            else:
                right += 1
            if left == right:
                longest = max(longest, 2 * right)
            elif right > left:
                left = right = 0
        
        left = right = 0
        for ch in reversed(s):
            if ch == '(':
                left += 1
            else:
                right += 1
            if left == right:
                longest = max(longest, 2 * left)
            elif left > right:
                left = right = 0
        
        return longest
