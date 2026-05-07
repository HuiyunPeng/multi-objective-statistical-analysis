class Solution:
    def countDigitOne(self, n: int) -> int:
        total = 0
        factor = 1
        
        while factor <= n:
            lower = n % factor
            curr = (n // factor) % 10
            higher = n // (factor * 10)
            
            if curr == 0:
                total += higher * factor
            elif curr == 1:
                total += higher * factor + lower + 1
            else:
                total += (higher + 1) * factor
            
            factor *= 10
        
        return total
