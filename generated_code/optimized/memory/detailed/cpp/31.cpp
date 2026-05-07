bool is_prime(long long n) {
    if (n < 2) return false;
    if ((n & 1LL) == 0) return n == 2;
    for (long long i = 3; i <= n / i; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
