long long special_factorial(int n) {
    if (n <= 0) return 1LL;

    static const long long precomputed[] = {
        1LL,                   // 0
        1LL,                   // 1
        2LL,                   // 2
        12LL,                  // 3
        288LL,                 // 4
        34560LL,               // 5
        24883200LL,            // 6
        125411328000LL,        // 7
        5056584744960000LL     // 8
    };

    if (n <= 8) return precomputed[n];

    long long fact = 40320LL;               // 8!
    long long bfact = precomputed[8];       // product of factorials up to 8!

    for (int i = 9; i <= n; ++i) {
        fact *= i;
        bfact *= fact;
    }

    return bfact;
}
