bool is_multiply_prime(int a){
    if (a < 2) return false;

    int count = 0;
    for (int i = 2; i <= a / i; ++i) {
        while (a % i == 0) {
            a /= i;
            if (++count > 3) return false;
        }
    }

    if (a > 1) ++count;
    return count == 3;
}
