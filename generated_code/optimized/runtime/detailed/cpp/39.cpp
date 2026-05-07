int prime_fib(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 2;
    if (n == 2) return 3;
    if (n == 3) return 5;

    auto isPrime = [](int x) -> bool {
        if (x <= 1) return false;
        if ((x & 1) == 0) return x == 2;
        if (x % 3 == 0) return x == 3;
        for (int d = 5; d <= x / d; d += 6) {
            if (x % d == 0 || x % (d + 2) == 0) return false;
        }
        return true;
    };

    int count = 3;
    int curr = 5; // F5
    int next = 8; // F6

    for (int idx = 6;; ++idx) {
        int sum = curr + next;
        curr = next;
        next = sum;

        // Prime Fibonacci numbers (except 3 = F4) can only occur at prime indices.
        if (!isPrime(idx)) continue;

        if (isPrime(curr) && ++count == n) {
            return curr;
        }
    }
}
