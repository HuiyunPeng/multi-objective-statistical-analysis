#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> arr) {
    auto bit_count = [](int x) {
        unsigned int u = x < 0 ? 0u - static_cast<unsigned int>(x)
                               : static_cast<unsigned int>(x);
        return __builtin_popcount(u);
    };

    sort(arr.begin(), arr.end(), [&](int a, int b) {
        int ca = bit_count(a);
        int cb = bit_count(b);
        return (ca < cb) || (ca == cb && a < b);
    });

    return arr;
}
