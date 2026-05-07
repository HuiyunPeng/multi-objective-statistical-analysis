#include <climits>

static inline bool is_prime(int x) {
    if (x < 2) return false;
    if ((x & 1) == 0) return x == 2;
    if (x % 3 == 0) return x == 3;
    for (int d = 5; d <= x / d; d += 6) {
        if (x % d == 0 || x % (d + 2) == 0) return false;
    }
    return true;
}

int prime_fib(int n) {
    if (n <= 0) return 0;

    struct Cache {
        int values[32];
        int size;
    };

    static const Cache cache = []() {
        Cache c = {{0}, 0};
        int a = 1, b = 1; // F1, F2

        for (int index = 3; b <= INT_MAX - a; ++index) {
            const int next = a + b; // F(index)
            a = b;
            b = next;

            if ((index == 4 || is_prime(index)) && is_prime(b)) {
                c.values[c.size++] = b;
            }
        }
        return c;
    }();

    return (n <= cache.size) ? cache.values[n - 1] : 0;
}
