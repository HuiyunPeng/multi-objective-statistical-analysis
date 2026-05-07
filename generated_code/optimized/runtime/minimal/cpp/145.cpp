#include <vector>
#include <algorithm>
using namespace std;

static inline int digit_score(int n) {
    long long x = n;
    if (x < 0) x = -x;

    int sum = 0, first = 0;
    do {
        int d = static_cast<int>(x % 10);
        sum += d;
        first = d;
        x /= 10;
    } while (x);

    return (n >= 0) ? sum : (sum - (first << 1));
}

vector<int> order_by_points(vector<int> nums) {
    const size_t n = nums.size();
    if (n < 2) return nums;

    vector<pair<int, int>> items;
    items.reserve(n);

    for (int v : nums) {
        items.emplace_back(digit_score(v), v);
    }

    stable_sort(items.begin(), items.end(),
                [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.first < b.first;
                });

    for (size_t i = 0; i < n; ++i) {
        nums[i] = items[i].second;
    }

    return nums;
}
