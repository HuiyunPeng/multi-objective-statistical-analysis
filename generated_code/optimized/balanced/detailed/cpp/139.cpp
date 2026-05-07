long long special_factorial(int n) {
    if (n <= 1) return 1;

    long long fact = 1;
    long long bfact = 1;

    for (int i = 2; i <= n; ++i) {
        fact *= i;
        bfact *= fact;
    }

    return bfact;
}
