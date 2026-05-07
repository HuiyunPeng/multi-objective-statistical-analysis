bool is_prime(long long n) {
    if (n < 2) return false;
    if (n < 4) return true;          // 2, 3
    if ((n & 1LL) == 0) return false; // even numbers > 2
    if (n % 3 == 0) return n == 3;

    for (long long i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
