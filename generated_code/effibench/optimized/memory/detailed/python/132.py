class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        cuts = list(range(-1, n))  # cuts[i] = min cuts for s[:i]

        for center in range(n):
            # Odd-length palindromes
            l = r = center
            while l >= 0 and r < n and s[l] == s[r]:
                new_cut = cuts[l] + 1
                if new_cut < cuts[r + 1]:
                    cuts[r + 1] = new_cut
                l -= 1
                r += 1

            # Even-length palindromes
            l, r = center, center + 1
            while l >= 0 and r < n and s[l] == s[r]:
                new_cut = cuts[l] + 1
                if new_cut < cuts[r + 1]:
                    cuts[r + 1] = new_cut
                l -= 1
                r += 1

        return cuts[n]
