#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

vector<int> sort_array(vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return arr;

    vector<uint64_t> keys;
    keys.reserve(n);

    for (int x : arr) {
        uint64_t mag = (x < 0) ? static_cast<uint64_t>(-(int64_t)x)
                               : static_cast<uint64_t>(x);
        uint64_t pop = static_cast<uint64_t>(__builtin_popcountll(mag));
        uint64_t signed_order = static_cast<uint32_t>(x) ^ 0x80000000u;
        keys.push_back((pop << 32) | signed_order);
    }

    sort(keys.begin(), keys.end());

    for (size_t i = 0; i < n; ++i) {
        uint32_t signed_order = static_cast<uint32_t>(keys[i]);
        arr[i] = static_cast<int>(signed_order ^ 0x80000000u);
    }

    return arr;
}
