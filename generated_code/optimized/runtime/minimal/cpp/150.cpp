int x_or_y(int n, int x, int y) {
    if (n < 2) return y;
    if (n == 2 || n == 3) return x;
    if (n % 2 == 0 || n % 3 == 0) return y;

    for (int i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return y;
    }
    return x;
}
