bool is_multiply_prime(int a) {
    if (a < 8) return false;

    int cnt = 0;

    while ((a & 1) == 0) {
        a >>= 1;
        if (++cnt > 3) return false;
    }

    for (int i = 3; i <= a / i; i += 2) {
        while (a % i == 0) {
            a /= i;
            if (++cnt > 3) return false;
        }
    }

    if (a > 1) ++cnt;

    return cnt == 3;
}
