int largest_divisor(int n) {
    if (n <= 1) return 1;
    if ((n & 1) == 0) return n >> 1;

    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) return n / i;
    }
    return 1;
}
