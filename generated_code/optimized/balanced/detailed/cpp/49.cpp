int modp(int n, int p) {
    if (p == 1) return 0;

    long long result = 1 % p;
    long long base = 2 % p;

    while (n > 0) {
        if (n & 1) result = (result * base) % p;
        base = (base * base) % p;
        n >>= 1;
    }

    return static_cast<int>(result);
}
