int digits(int n) {
    int prod = 1;
    bool has = false;

    while (n != 0) {
        int d = n % 10;
        if (d < 0) d = -d;
        if (d & 1) {
            has = true;
            prod *= d;
        }
        n /= 10;
    }

    return has ? prod : 0;
}
