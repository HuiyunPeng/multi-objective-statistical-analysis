class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        cuts = list(range(n))

        for center in range(n):
            # Odd-length palindromes
            left = right = center
            while left >= 0 and right < n and s[left] == s[right]:
                new_cut = 0 if left == 0 else cuts[left - 1] + 1
                if new_cut < cuts[right]:
                    cuts[right] = new_cut
                left -= 1
                right += 1

            # Even-length palindromes
            left, right = center - 1, center
            while left >= 0 and right < n and s[left] == s[right]:
                new_cut = 0 if left == 0 else cuts[left - 1] + 1
                if new_cut < cuts[right]:
                    cuts[right] = new_cut
                left -= 1
                right += 1

        return cuts[-1]
