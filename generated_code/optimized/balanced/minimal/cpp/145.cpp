#include <vector>
#include <algorithm>
using namespace std;

vector<int> order_by_points(vector<int> nums) {
    struct Node {
        int key;
        int idx;
        int val;
    };

    auto calc_key = [](int x) -> int {
        if (x == 0) return 0;

        long long v = x;
        if (v < 0) v = -v;

        int sum = 0;
        int msd = 0;
        while (v > 0) {
            int d = static_cast<int>(v % 10);
            sum += d;
            msd = d;
            v /= 10;
        }

        return x > 0 ? sum : sum - 2 * msd;
    };

    const int n = static_cast<int>(nums.size());
    vector<Node> arr;
    arr.reserve(n);

    for (int i = 0; i < n; ++i) {
        arr.push_back({calc_key(nums[i]), i, nums[i]});
    }

    sort(arr.begin(), arr.end(), [](const Node& a, const Node& b) {
        if (a.key != b.key) return a.key < b.key;
        return a.idx < b.idx;
    });

    for (int i = 0; i < n; ++i) {
        nums[i] = arr[i].val;
    }

    return nums;
}
