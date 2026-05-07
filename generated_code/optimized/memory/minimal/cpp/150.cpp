int x_or_y(int n, int x, int y) {
    if (n < 2) return y;
    if (n == 2) return x;
    if ((n & 1) == 0) return y;

    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) return y;
    }
    return x;
}
