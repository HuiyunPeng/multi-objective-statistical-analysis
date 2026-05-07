int digits(int n) {
    int prod = 1;
    bool has = false;
    long long x = n;

    if (x < 0) {
        prod = -3;   // preserves original behavior for '-'
        has = true;
        x = -x;
    }

    if (x == 0) {
        return has ? prod : 0;
    }

    while (x > 0) {
        int d = static_cast<int>(x % 10);
        if (d & 1) {
            has = true;
            prod *= d;
        }
        x /= 10;
    }

    return has ? prod : 0;
}
