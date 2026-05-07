#include <vector>
using namespace std;

static inline bool isPalindrome(int x) {
    int original = x, reversed = 0;
    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    return original == reversed;
}

vector<int> even_odd_palindrome(int n) {
    int even = 0, odd = 0;
    for (int i = 1; i <= n; ++i) {
        if (isPalindrome(i)) {
            if (i & 1) ++odd;
            else ++even;
        }
    }
    return {even, odd};
}
