#include <vector>
using namespace std;

vector<int> even_odd_count(long long num) {
    int even = 0, odd = 0;

    unsigned long long x = (num < 0)
        ? 0ULL - static_cast<unsigned long long>(num)
        : static_cast<unsigned long long>(num);

    if (x == 0) return {1, 0};

    while (x > 0) {
        int digit = static_cast<int>(x % 10);
        if (digit & 1) ++odd;
        else ++even;
        x /= 10;
    }

    return {even, odd};
}
