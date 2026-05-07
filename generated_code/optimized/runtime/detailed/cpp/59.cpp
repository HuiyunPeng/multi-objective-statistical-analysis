int largest_prime_factor(int n) {
    if (n <= 1) return n;

    int largest = 1;

    while ((n & 1) == 0) {
        largest = 2;
        n >>= 1;
    }

    for (int i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    return (n > 1) ? n : largest;
}
