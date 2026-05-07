#include <vector>
using namespace std;

static inline long long make_palindrome(int prefix, bool odd_length) {
    long long result = prefix;
    if (odd_length) prefix /= 10;
    while (prefix > 0) {
        result = result * 10 + (prefix % 10);
        prefix /= 10;
    }
    return result;
}

vector<int> even_odd_palindrome(int n) {
    if (n <= 0) return {0, 0};

    int even = 0, odd = 0;

    int digits = 0;
    for (int x = n; x > 0; x /= 10) ++digits;

    const int pow10[] = {1, 10, 100, 1000, 10000, 100000};

    for (int len = 1; len < digits; ++len) {
        int half = (len + 1) / 2;
        int block = pow10[half - 1];
        odd += 5 * block;
        even += 4 * block;
    }

    int len = digits;
    int half = (len + 1) / 2;
    int block = pow10[half - 1];
    int shift = len - half;
    int prefix = n / pow10[shift];
    int upper = prefix - 1;

    if (upper >= block) {
        int first_digit = upper / block;
        int remainder = upper % block;

        odd += (first_digit / 2) * block;
        even += ((first_digit - 1) / 2) * block;

        if (first_digit & 1) {
            odd += remainder + 1;
        } else {
            even += remainder + 1;
        }
    }

    if (make_palindrome(prefix, (len & 1) != 0) <= n) {
        if ((prefix / block) & 1) {
            ++odd;
        } else {
            ++even;
        }
    }

    return {even, odd};
}
