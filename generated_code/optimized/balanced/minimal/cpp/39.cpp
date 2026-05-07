#include <cstdint>

static inline uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

static inline bool isPrime32(uint32_t n) {
    if (n < 2) return false;
    if ((n & 1u) == 0) return n == 2;
    if (n % 3u == 0) return n == 3;
    if (n % 5u == 0) return n == 5;
    if (n % 7u == 0) return n == 7;

    uint32_t d = n - 1;
    uint32_t s = 0;
    while ((d & 1u) == 0) {
        d >>= 1;
        ++s;
    }

    const uint32_t bases[] = {2u, 3u, 5u, 7u};
    for (uint32_t a : bases) {
        if (a >= n) continue;
        uint64_t x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (uint32_t r = 1; r < s; ++r) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

static inline bool isPrimeIndex(int x) {
    if (x < 2) return false;
    if ((x & 1) == 0) return x == 2;
    if (x % 3 == 0) return x == 3;
    for (int i = 5; i <= x / i; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

int prime_fib(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 2;
    if (n == 2) return 3;
    if (n == 3) return 5;

    int count = 3;
    int index = 5;
    int64_t a = 3, b = 5; // F4, F5

    while (true) {
        ++index;
        int64_t c = a + b;
        a = b;
        b = c;

        if (c > 0x7fffffffLL) return 0;

        if (isPrimeIndex(index) && isPrime32(static_cast<uint32_t>(c))) {
            if (++count == n) return static_cast<int>(c);
        }
    }
}
