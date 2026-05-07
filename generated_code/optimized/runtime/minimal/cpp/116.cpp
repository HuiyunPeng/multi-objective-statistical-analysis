#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> arr) {
    struct Item {
        int value;
        int bits;
    };

    vector<Item> items;
    items.reserve(arr.size());

    for (int x : arr) {
        unsigned int ux = static_cast<unsigned int>(x);
        unsigned int mag = (x < 0) ? (0u - ux) : ux;
        items.push_back({x, __builtin_popcount(mag)});
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        if (a.bits != b.bits) return a.bits < b.bits;
        return a.value < b.value;
    });

    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = items[i].value;
    }

    return arr;
}
