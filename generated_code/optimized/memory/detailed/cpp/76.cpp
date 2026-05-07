bool is_simple_power(int x, int n) {
    int p = 1;
    for (int count = 0; count < 100 && p <= x; ++count) {
        if (p == x) return true;
        p *= n;
    }
    return false;
}
