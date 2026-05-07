#include <vector>
using namespace std;

vector<int> even_odd_count(long long num) {
    unsigned long long x = num < 0
        ? 0ULL - static_cast<unsigned long long>(num)
        : static_cast<unsigned long long>(num);

    int even = 0, odd = 0;

    if (x == 0) return {1, 0};

    while (x) {
        if ((x % 10) & 1ULL) ++odd;
        else ++even;
        x /= 10;
    }

    return {even, odd};
}
