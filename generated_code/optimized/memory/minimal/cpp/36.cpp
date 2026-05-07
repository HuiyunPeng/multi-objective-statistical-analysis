int fizz_buzz(int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 11 == 0 || i % 13 == 0) {
            for (int q = i; q > 0; q /= 10) {
                count += (q % 10 == 7);
            }
        }
    }
    return count;
}
