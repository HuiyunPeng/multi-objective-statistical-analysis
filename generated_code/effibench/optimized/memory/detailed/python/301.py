class Solution:
    def removeInvalidParentheses(self, s: str):
        n = len(s)

        # Minimum removals needed.
        lrem = rrem = 0
        for ch in s:
            if ch == '(':
                lrem += 1
            elif ch == ')':
                if lrem:
                    lrem -= 1
                else:
                    rrem += 1

        # Suffix counts for pruning.
        rem_paren = [0] * (n + 1)
        rem_close = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            ch = s[i]
            rem_paren[i] = rem_paren[i + 1] + (1 if ch == '(' or ch == ')' else 0)
            rem_close[i] = rem_close[i + 1] + (1 if ch == ')' else 0)

        res = set()
        path = []

        def dfs(i: int, balance: int, l: int, r: int) -> None:
            if l < 0 or r < 0 or balance < 0:
                return
            if l + r > rem_paren[i]:
                return
            if balance > rem_close[i]:
                return

            if i == n:
                if balance == 0 and l == 0 and r == 0:
                    res.add(''.join(path))
                return

            ch = s[i]

            if ch == '(':
                # Remove it.
                if l:
                    dfs(i + 1, balance, l - 1, r)

                # Keep it.
                path.append(ch)
                dfs(i + 1, balance + 1, l, r)
                path.pop()

            elif ch == ')':
                # Remove it.
                if r:
                    dfs(i + 1, balance, l, r - 1)

                # Keep it only if it can match a previous '('.
                if balance:
                    path.append(ch)
                    dfs(i + 1, balance - 1, l, r)
                    path.pop()

            else:
                path.append(ch)
                dfs(i + 1, balance, l, r)
                path.pop()

        dfs(0, 0, lrem, rrem)
        return list(res)
