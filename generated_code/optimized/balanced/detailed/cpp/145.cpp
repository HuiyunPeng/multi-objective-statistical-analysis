#include <vector>
#include <algorithm>

using namespace std;

static inline int compute_points(int num) noexcept {
    long long x = num;
    unsigned long long ux = x < 0
        ? static_cast<unsigned long long>(-x)
        : static_cast<unsigned long long>(x);

    int sum = 0;
    int first = 0;

    do {
        int digit = static_cast<int>(ux % 10);
        sum += digit;
        first = digit;
        ux /= 10;
    } while (ux != 0);

    return (num > 0) ? sum : (sum - (first << 1));
}

vector<int> order_by_points(vector<int> nums) {
    const int n = static_cast<int>(nums.size());
    if (n < 2) return nums;

    struct Item {
        int key;
        int index;
        int value;
    };

    vector<Item> items;
    items.reserve(n);

    for (int i = 0; i < n; ++i) {
        items.push_back({compute_points(nums[i]), i, nums[i]});
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (a.key < b.key) || (a.key == b.key && a.index < b.index);
    });

    for (int i = 0; i < n; ++i) {
        nums[i] = items[i].value;
    }

    return nums;
}
