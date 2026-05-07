#include <vector>
using namespace std;

vector<int> even_odd_count(long long num) {
    unsigned long long x = static_cast<unsigned long long>(num);
    if (num < 0) x = 0ULL - x;

    int even = 0, odd = 0;

    if (x == 0) return {1, 0};

    while (x) {
        if ((x % 10ULL) & 1ULL) ++odd;
        else ++even;
        x /= 10ULL;
    }

    return {even, odd};
}
