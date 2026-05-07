int modp(int n, int p) {
    int result = 1;
    if (n <= 0) return result;

    int base = 2 % p;
    while (n > 0) {
        if (n & 1) result = static_cast<int>((static_cast<long long>(result) * base) % p);
        n >>= 1;
        if (n) base = static_cast<int>((static_cast<long long>(base) * base) % p);
    }

    return result;
}
