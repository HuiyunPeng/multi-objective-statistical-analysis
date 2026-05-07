int largest_prime_factor(int n) {
    if (n <= 3) return n;

    while ((n & 1) == 0 && n > 2) n >>= 1;
    while (n % 3 == 0 && n > 3) n /= 3;

    for (int i = 5; i <= n / i; i += 6) {
        while (n % i == 0 && n > i) n /= i;

        const int j = i + 2;
        while (n % j == 0 && n > j) n /= j;
    }

    return n;
}
