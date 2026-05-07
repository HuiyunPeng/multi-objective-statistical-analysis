bool is_multiply_prime(int a) {
    unsigned char num = 0;
    for (int i = 2; i <= a / i; ++i) {
        while (a > i && a % i == 0) {
            a /= i;
            if (++num > 2) return false;
        }
    }
    return num == 2;
}
