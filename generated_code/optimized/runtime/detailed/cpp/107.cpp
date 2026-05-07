#include <vector>
using namespace std;

vector<int> even_odd_palindrome(int n) {
    if (n <= 0) return {0, 0};

    long long pow10[11];
    pow10[0] = 1;
    for (int i = 1; i < 11; ++i) pow10[i] = pow10[i - 1] * 10LL;

    auto make_palindrome = [](long long prefix, bool odd_length) -> long long {
        long long result = prefix;
        long long x = odd_length ? prefix / 10 : prefix;
        while (x > 0) {
            result = result * 10 + (x % 10);
            x /= 10;
        }
        return result;
    };

    auto count_prefixes_by_parity = [&](long long limit, int k, bool odd_first_digit) -> long long {
        if (limit < pow10[k - 1]) return 0;
        long long block = pow10[k - 1];
        long long count = 0;
        for (int d = odd_first_digit ? 1 : 2; d <= 9; d += 2) {
            long long start = (long long)d * block;
            if (limit < start) continue;
            long long end = start + block - 1;
            count += (limit < end ? limit : end) - start + 1;
        }
        return count;
    };

    int len = 0;
    for (int x = n; x > 0; x /= 10) ++len;

    long long even_count = 0, odd_count = 0;

    for (int L = 1; L < len; ++L) {
        int k = (L + 1) / 2;
        long long ways = pow10[k - 1];
        odd_count += 5 * ways;
        even_count += 4 * ways;
    }

    int k = (len + 1) / 2;
    long long prefix = n / pow10[len - k];
    long long prefix_less = prefix - 1;

    odd_count += count_prefixes_by_parity(prefix_less, k, true);
    even_count += count_prefixes_by_parity(prefix_less, k, false);

    long long pal = make_palindrome(prefix, (len & 1) != 0);
    int first_digit = (int)(prefix / pow10[k - 1]);
    if (pal <= n) {
        if (first_digit & 1) ++odd_count;
        else ++even_count;
    }

    return {(int)even_count, (int)odd_count};
}
