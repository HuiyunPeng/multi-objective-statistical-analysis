bool is_multiply_prime(int a) {
    if (a < 8) return false;

    int count = 0;

    while ((a & 1) == 0) {
        a >>= 1;
        if (++count == 3) return a == 1;
    }

    while (a % 3 == 0) {
        a /= 3;
        if (++count == 3) return a == 1;
    }

    for (int i = 5; 1LL * i * i <= a; i += 6) {
        while (a % i == 0) {
            a /= i;
            if (++count == 3) return a == 1;
        }

        int j = i + 2;
        while (a % j == 0) {
            a /= j;
            if (++count == 3) return a == 1;
        }
    }

    return count + (a > 1) == 3;
}
