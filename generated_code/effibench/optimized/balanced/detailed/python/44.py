class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n = len(s)

        # Collapse consecutive '*' to reduce unnecessary work.
        if '*' in p:
            parts = []
            prev_star = False
            for ch in p:
                if ch == '*':
                    if not prev_star:
                        parts.append(ch)
                        prev_star = True
                else:
                    parts.append(ch)
                    prev_star = False
            p = ''.join(parts)

        # Quick fail: non-'*' chars must each match one character.
        if len(p) - p.count('*') > n:
            return False

        i = j = 0
        m = len(p)
        star = -1
        match = 0

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
