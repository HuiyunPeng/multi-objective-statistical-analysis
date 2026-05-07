#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> arr) {
    auto bit_count_abs = [](int x) -> int {
        unsigned long long v = x < 0
            ? static_cast<unsigned long long>(-(long long)x)
            : static_cast<unsigned long long>(x);
        return __builtin_popcountll(v);
    };

    sort(arr.begin(), arr.end(), [&](int a, int b) {
        int ca = bit_count_abs(a);
        int cb = bit_count_abs(b);
        return ca != cb ? ca < cb : a < b;
    });

    return arr;
}
