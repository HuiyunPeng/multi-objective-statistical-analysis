long long special_factorial(int n) {
    long long fact = 1;
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
        result *= fact;
    }
    return result;
}
