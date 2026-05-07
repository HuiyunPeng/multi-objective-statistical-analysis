class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        cuts = list(range(n))
        
        for center in range(n):
            # Odd-length palindromes
            l = r = center
            while l >= 0 and r < n and s[l] == s[r]:
                cuts[r] = 0 if l == 0 else min(cuts[r], cuts[l - 1] + 1)
                l -= 1
                r += 1
            
            # Even-length palindromes
            l, r = center - 1, center
            while l >= 0 and r < n and s[l] == s[r]:
                cuts[r] = 0 if l == 0 else min(cuts[r], cuts[l - 1] + 1)
                l -= 1
                r += 1
        
        return cuts[-1]
