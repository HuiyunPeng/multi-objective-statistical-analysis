class Solution:
    def removeInvalidParentheses(self, s: str):
        left_rem = right_rem = 0
        for ch in s:
            if ch == '(':
                left_rem += 1
            elif ch == ')':
                if left_rem > 0:
                    left_rem -= 1
                else:
                    right_rem += 1

        res = set()
        n = len(s)
        path = []

        def dfs(i, balance, lrem, rrem):
            if i == n:
                if balance == 0 and lrem == 0 and rrem == 0:
                    res.add(''.join(path))
                return

            # Not enough characters left to remove required parentheses
            if n - i < lrem + rrem:
                return

            ch = s[i]

            if ch == '(':
                # Remove it
                if lrem > 0:
                    dfs(i + 1, balance, lrem - 1, rrem)

                # Keep it
                path.append(ch)
                dfs(i + 1, balance + 1, lrem, rrem)
                path.pop()

            elif ch == ')':
                # Remove it
                if rrem > 0:
                    dfs(i + 1, balance, lrem, rrem - 1)

                # Keep it only if valid
                if balance > 0:
                    path.append(ch)
                    dfs(i + 1, balance - 1, lrem, rrem)
                    path.pop()

            else:
                path.append(ch)
                dfs(i + 1, balance, lrem, rrem)
                path.pop()

        dfs(0, 0, left_rem, right_rem)
        return list(res)
