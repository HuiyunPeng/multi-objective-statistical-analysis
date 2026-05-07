#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> arr) {
    struct Item {
        int bits;
        int value;
    };

    const int n = static_cast<int>(arr.size());
    vector<Item> items;
    items.reserve(n);

    for (int x : arr) {
        unsigned int ax = (x < 0)
            ? static_cast<unsigned int>(-(long long)x)
            : static_cast<unsigned int>(x);
        items.push_back({__builtin_popcount(ax), x});
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (a.bits < b.bits) || (a.bits == b.bits && a.value < b.value);
    });

    for (int i = 0; i < n; ++i) {
        arr[i] = items[i].value;
    }

    return arr;
}
