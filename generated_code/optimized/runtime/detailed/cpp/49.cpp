int modp(int n, int p) {
    if (n <= 0) return 1;
    if (p == 1) return 0;

    long long result = 1;
    long long base = 2 % p;

    while (n > 0) {
        if (n & 1) result = (result * base) % p;
        n >>= 1;
        if (n) base = (base * base) % p;
    }

    return (int)result;
}
