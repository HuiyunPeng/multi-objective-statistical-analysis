static inline int count_sevens(int x) {
    int count = 0;
    while (x > 0) {
        count += (x % 10 == 7);
        x /= 10;
    }
    return count;
}

int fizz_buzz(int n) {
    if (n <= 0) return 0;

    int count = 0;

    for (int i = 11; i < n; i += 11)
        count += count_sevens(i);

    for (int i = 13; i < n; i += 13)
        count += count_sevens(i);

    for (int i = 143; i < n; i += 143)
        count -= count_sevens(i);

    return count;
}
