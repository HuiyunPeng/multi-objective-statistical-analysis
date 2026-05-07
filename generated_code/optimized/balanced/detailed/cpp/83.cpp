int starts_one_ends(int n) {
    if (n < 1) return 0;

    static const int precomputed[] = {
        0,
        1,
        18,
        180,
        1800,
        18000,
        180000,
        1800000,
        18000000,
        180000000,
        1800000000
    };

    if (n <= 10) return precomputed[n];

    int out = precomputed[10];
    for (int i = 10; i < n; ++i) {
        out *= 10;
    }
    return out;
}
