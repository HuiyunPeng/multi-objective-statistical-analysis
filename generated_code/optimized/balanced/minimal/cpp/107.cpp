#include <vector>
using namespace std;

vector<int> even_odd_palindrome(int n) {
    if (n <= 0) return {0, 0};

    static const long long p10[] = {
        1LL,
        10LL,
        100LL,
        1000LL,
        10000LL,
        100000LL,
        1000000LL,
        10000000LL,
        100000000LL,
        1000000000LL,
        10000000000LL
    };

    int len = 0;
    for (int x = n; x > 0; x /= 10) ++len;

    long long even = 0, odd = 0;

    for (int L = 1; L < len; ++L) {
        long long cnt = p10[(L - 1) / 2];
        odd += 5 * cnt;
        even += 4 * cnt;
    }

    int half = (len + 1) / 2;
    long long block = p10[half - 1];
    long long prefix = n / p10[len - half];

    long long pal = prefix;
    for (long long x = (len & 1) ? prefix / 10 : prefix; x > 0; x /= 10) {
        pal = pal * 10 + (x % 10);
    }

    long long endPrefix = prefix - 1 + (pal <= (long long)n);
    if (endPrefix >= block) {
        long long leading = endPrefix / block;
        long long rem = endPrefix % block;
        long long full = leading - 1;

        odd += ((full + 1) / 2) * block;
        even += (full / 2) * block;

        if (leading & 1) odd += rem + 1;
        else even += rem + 1;
    }

    return {(int)even, (int)odd};
}
