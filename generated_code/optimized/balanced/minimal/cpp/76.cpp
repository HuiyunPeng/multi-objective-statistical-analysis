bool is_simple_power(int x, int n) {
    if (x == 1) return true;

    if (n == 0) return x == 0;
    if (n == 1) return false;
    if (n == -1) return x == -1;
    if (x == 0) return false;

    while (x % n == 0) {
        x /= n;
    }

    return x == 1;
}
