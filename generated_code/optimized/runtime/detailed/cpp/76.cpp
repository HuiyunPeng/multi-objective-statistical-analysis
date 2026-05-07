bool is_simple_power(int x, int n) {
    if (x == 1) return true;
    if (x < 1) return false;

    if (n > 1) {
        while (x % n == 0) x /= n;
        return x == 1;
    }

    if (n < -1) {
        long long base = 1LL * n * n;
        long long v = x;
        while (v % base == 0) v /= base;
        return v == 1;
    }

    return false;
}
