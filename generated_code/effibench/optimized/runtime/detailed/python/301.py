class Solution:
    def removeInvalidParentheses(self, s: str):
        n = len(s)

        # Compute the minimum number of '(' and ')' that must be removed.
        left_remove = right_remove = 0
        for ch in s:
            if ch == '(':
                left_remove += 1
            elif ch == ')':
                if left_remove > 0:
                    left_remove -= 1
                else:
                    right_remove += 1

        # Suffix counts for pruning.
        suffix_open = [0] * (n + 1)
        suffix_close = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            suffix_open[i] = suffix_open[i + 1] + (1 if s[i] == '(' else 0)
            suffix_close[i] = suffix_close[i + 1] + (1 if s[i] == ')' else 0)

        res = set()
        path = []
        dead = set()  # states proven to lead to no valid completion

        def dfs(i: int, balance: int, lrem: int, rrem: int) -> bool:
            state = (i, balance, lrem, rrem)
            if state in dead:
                return False

            # Pruning
            if n - i < lrem + rrem:
                dead.add(state)
                return False
            if lrem > suffix_open[i] or rrem > suffix_close[i]:
                dead.add(state)
                return False
            if balance > suffix_close[i]:
                dead.add(state)
                return False

            if i == n:
                if balance == 0 and lrem == 0 and rrem == 0:
                    res.add(''.join(path))
                    return True
                dead.add(state)
                return False

            ch = s[i]
            found = False

            if ch == '(':
                if lrem > 0:
                    found = dfs(i + 1, balance, lrem - 1, rrem) or found

                path.append(ch)
                found = dfs(i + 1, balance + 1, lrem, rrem) or found
                path.pop()

            elif ch == ')':
                if rrem > 0:
                    found = dfs(i + 1, balance, lrem, rrem - 1) or found

                if balance > 0:
                    path.append(ch)
                    found = dfs(i + 1, balance - 1, lrem, rrem) or found
                    path.pop()

            else:
                path.append(ch)
                found = dfs(i + 1, balance, lrem, rrem) or found
                path.pop()

            if not found:
                dead.add(state)
            return found

        dfs(0, 0, left_remove, right_remove)
        return list(res)
