int starts_one_ends(int n) {
    if (n < 1) return 0;
    if (n == 1) return 1;

    static const int pow10[] = {
        1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000
    };

    if (n <= 10) return 18 * pow10[n - 2];

    int out = 18;
    for (int k = n - 2; k > 0; --k) out *= 10;
    return out;
}
