bool is_multiply_prime(int a) {
    if (a < 8) return false;

    int cnt = 0;

    while ((a & 1) == 0) {
        a >>= 1;
        if (++cnt > 3) return false;
    }

    while (a % 3 == 0) {
        a /= 3;
        if (++cnt > 3) return false;
    }

    for (int i = 5; 1LL * i * i <= a; i += 6) {
        while (a % i == 0) {
            a /= i;
            if (++cnt > 3) return false;
        }

        int j = i + 2;
        while (a % j == 0) {
            a /= j;
            if (++cnt > 3) return false;
        }
    }

    if (a > 1) ++cnt;
    return cnt == 3;
}
