bool is_multiply_prime(int a) {
    if (a < 8) return false; // Smallest product of 3 primes is 2*2*2 = 8

    int count = 0;

    while ((a & 1) == 0) {
        a >>= 1;
        if (++count > 3) return false;
    }

    for (int d = 3; d <= a / d; d += 2) {
        while (a % d == 0) {
            a /= d;
            if (++count > 3) return false;
        }
    }

    if (a > 1) ++count;

    return count == 3;
}
