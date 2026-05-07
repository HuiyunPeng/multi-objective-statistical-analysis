bool is_simple_power(int x, int n) {
    if (x == 1) return true;
    if (x <= 0) return false;

    if (n == 0 || n == 1 || n == -1) return false;

    long long value = x;

    if (n > 1) {
        while (value % n == 0) value /= n;
        return value == 1;
    }

    long long base = -(long long)n; // abs(n) for n < -1
    int parity = 0;

    while (value % base == 0) {
        value /= base;
        parity ^= 1;
    }

    return value == 1 && parity == 0;
}
