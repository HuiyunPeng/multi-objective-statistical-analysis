class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        cuts = list(range(n))  # worst case: cut before every character

        for center in range(n):
            # Odd-length palindromes
            l = r = center
            while l >= 0 and r < n and s[l] == s[r]:
                if l == 0:
                    cuts[r] = 0
                else:
                    cuts[r] = min(cuts[r], cuts[l - 1] + 1)
                l -= 1
                r += 1

            # Even-length palindromes
            l, r = center - 1, center
            while l >= 0 and r < n and s[l] == s[r]:
                if l == 0:
                    cuts[r] = 0
                else:
                    cuts[r] = min(cuts[r], cuts[l - 1] + 1)
                l -= 1
                r += 1

        return cuts[-1]
