long long special_factorial(int n) {
    long long fact = 1, bfact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
        bfact *= fact;
    }
    return bfact;
}
