#include <vector>
#include <algorithm>
using namespace std;

vector<int> order_by_points(vector<int> nums) {
    struct Item {
        int value;
        int key;
        int index;
    };

    const int n = static_cast<int>(nums.size());
    vector<Item> items;
    items.reserve(n);

    for (int i = 0; i < n; ++i) {
        long long x = nums[i];
        long long ax = x < 0 ? -x : x;

        int total = 0;
        int first = 0;

        if (ax == 0) {
            first = 0;
        } else {
            while (ax >= 10) {
                total += static_cast<int>(ax % 10);
                ax /= 10;
            }
            first = static_cast<int>(ax);
            total += first;
        }

        int key = (nums[i] >= 0) ? total : (total - (first << 1));
        items.push_back({nums[i], key, i});
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (a.key < b.key) || (a.key == b.key && a.index < b.index);
    });

    for (int i = 0; i < n; ++i) {
        nums[i] = items[i].value;
    }

    return nums;
}
