#include <vector>
using namespace std;

vector<int> even_odd_count(long long num) {
    int even = 0, odd = 0;

    if (num == 0) return vector<int>{1, 0};

    while (num != 0) {
        int digit = static_cast<int>(num % 10);
        if (digit < 0) digit = -digit;

        if (digit % 2 == 0) ++even;
        else ++odd;

        num /= 10;
    }

    return vector<int>{even, odd};
}
