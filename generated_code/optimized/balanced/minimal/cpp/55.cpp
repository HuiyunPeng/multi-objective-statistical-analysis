int fib(int n) {
    if (n <= 1) return n;

    long long a = 0, b = 1;
    unsigned int mask = 1u;
    while (mask <= static_cast<unsigned int>(n >> 1)) mask <<= 1;

    while (mask) {
        long long d = a * ((b << 1) - a);
        long long e = a * a + b * b;

        if (n & static_cast<int>(mask)) {
            a = e;
            b = d + e;
        } else {
            a = d;
            b = e;
        }

        mask >>= 1;
    }

    return static_cast<int>(a);
}
