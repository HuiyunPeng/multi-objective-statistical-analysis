bool is_simple_power(int x, int n) {
    if (x == 1) return true;
    if (x <= 0) return false;

    if (n > 1) {
        while (x % n == 0) x /= n;
        return x == 1;
    }

    if (n >= -1) return false; // n is 1, 0, or -1

    const long long base = -(long long)n;
    bool odd_power = false;

    while (x % base == 0) {
        x = static_cast<int>(x / base);
        odd_power = !odd_power;
    }

    return x == 1 && !odd_power;
}
