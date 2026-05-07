int modp(int n, int p) {
    if (n <= 0) return 1 % p;

    long long result = 1 % p;
    long long base = 2 % p;

    while (n > 0) {
        if (n & 1) result = (result * base) % p;
        base = (base * base) % p;
        n >>= 1;
    }

    return (int)result;
}
