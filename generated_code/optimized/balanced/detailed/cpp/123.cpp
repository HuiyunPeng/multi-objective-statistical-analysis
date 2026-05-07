#include <vector>
#include <algorithm>
using namespace std;

vector<int> get_odd_collatz(int n) {
    vector<int> out;
    out.reserve(16);
    out.push_back(1);

    while ((n & 1) == 0) {
        n >>= 1;
    }

    while (n != 1) {
        out.push_back(n);
        long long next = 3LL * n + 1;
        next >>= __builtin_ctzll(static_cast<unsigned long long>(next));
        n = static_cast<int>(next);
    }

    sort(out.begin(), out.end());
    return out;
}
