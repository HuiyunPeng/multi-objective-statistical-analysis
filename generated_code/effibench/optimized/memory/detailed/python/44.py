class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        i = 0  # index in s
        j = 0  # index in p
        star = -1  # most recent '*' position in p
        match = 0  # position in s matched by that '*'

        n = len(s)
        m = len(p)

        while i < n:
            if j < m and (p[j] == s[i] or p[j] == '?'):
                i += 1
                j += 1
            elif j < m and p[j] == '*':
                star = j
                match = i
                j += 1
            elif star != -1:
                j = star + 1
                match += 1
                i = match
            else:
                return False

        while j < m and p[j] == '*':
            j += 1

        return j == m
