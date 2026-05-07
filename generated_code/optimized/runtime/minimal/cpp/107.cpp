#include <vector>
using namespace std;

static inline long long make_pal(long long half, int len) {
    long long res = half;
    long long x = (len & 1) ? (half / 10) : half;
    while (x) {
        res = res * 10 + (x % 10);
        x /= 10;
    }
    return res;
}

vector<int> even_odd_palindrome(int n) {
    if (n <= 0) return {0, 0};

    static const long long pow10[] = {
        1LL, 10LL, 100LL, 1000LL, 10000LL,
        100000LL, 1000000LL, 10000000LL, 100000000LL,
        1000000000LL, 10000000000LL
    };

    int L = 0, t = n;
    while (t) {
        ++L;
        t /= 10;
    }

    long long even = 0, odd = 0;

    for (int len = 1; len < L; ++len) {
        int halfLen = (len + 1) >> 1;
        long long block = pow10[halfLen - 1];
        odd += 5LL * block;
        even += 4LL * block;
    }

    int halfLen = (L + 1) >> 1;
    long long block = pow10[halfLen - 1];
    long long prefix = n / pow10[L - halfLen];
    long long firstDigit = prefix / block;
    long long rest = prefix % block;

    odd += (firstDigit / 2) * block + ((firstDigit & 1) ? rest : 0);
    even += ((firstDigit - 1) / 2) * block + ((firstDigit & 1) ? 0 : rest);

    if (make_pal(prefix, L) <= n) {
        if (firstDigit & 1) ++odd;
        else ++even;
    }

    return {(int)even, (int)odd};
}
