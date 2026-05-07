int starts_one_ends(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int out = 18;
    while (--n > 2) {
        out *= 10;
    }
    return out;
}
