int fib(int n) {
    if (n <= 1) return n;

    long long a = 0, b = 1;
    unsigned int x = static_cast<unsigned int>(n);
    int bit = 31;
    while (((x >> bit) & 1U) == 0) --bit;

    for (; bit >= 0; --bit) {
        long long d = a * ((b << 1) - a);
        long long e = a * a + b * b;
        if ((x >> bit) & 1U) {
            a = e;
            b = d + e;
        } else {
            a = d;
            b = e;
        }
    }

    return static_cast<int>(a);
}
