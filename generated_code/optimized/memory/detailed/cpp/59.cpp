int largest_prime_factor(int n) {
    while ((n & 1) == 0 && n > 2) {
        n >>= 1;
    }
    for (int i = 3; i <= n / i; i += 2) {
        while (n % i == 0 && n > i) {
            n /= i;
        }
    }
    return n;
}
