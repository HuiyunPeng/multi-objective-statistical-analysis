class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        # Collapse consecutive '*' to speed up matching.
        if '*' in p:
            compressed = []
            prev_star = False
            for ch in p:
                if ch == '*':
                    if not prev_star:
                        compressed.append(ch)
                    prev_star = True
                else:
                    compressed.append(ch)
                    prev_star = False
            p = ''.join(compressed)

        # If the number of non-'*' pattern characters exceeds s length, impossible.
        if sum(ch != '*' for ch in p) > len(s):
            return False

        i = j = 0
        star_idx = -1
        match_idx = 0
        n, m = len(s), len(p)

        while i < n:
            if j < m and (p[j] == s[i] or p[j] == '?'):
                i += 1
                j += 1
            elif j < m and p[j] == '*':
                star_idx = j
                match_idx = i
                j += 1
            elif star_idx != -1:
                j = star_idx + 1
                match_idx += 1
                i = match_idx
            else:
                return False

        while j < m and p[j] == '*':
            j += 1

        return j == m
