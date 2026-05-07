class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        cuts = list(range(n))  # worst case: cut before every character

        for center in range(n):
            # Odd-length palindromes
            left = right = center
            while left >= 0 and right < n and s[left] == s[right]:
                if left == 0:
                    cuts[right] = 0
                else:
                    cuts[right] = min(cuts[right], cuts[left - 1] + 1)
                left -= 1
                right += 1

            # Even-length palindromes
            left, right = center, center + 1
            while left >= 0 and right < n and s[left] == s[right]:
                if left == 0:
                    cuts[right] = 0
                else:
                    cuts[right] = min(cuts[right], cuts[left - 1] + 1)
                left -= 1
                right += 1

        return cuts[-1]
