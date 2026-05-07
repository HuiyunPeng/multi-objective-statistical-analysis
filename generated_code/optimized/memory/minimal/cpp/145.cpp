#include <vector>
using namespace std;

static int point_sum(int x) {
    long long a = x < 0 ? -(long long)x : (long long)x;
    if (a == 0) return 0;

    int total = 0;
    long long t = a;
    while (t >= 10) t /= 10;
    int first = (int)t;

    while (a > 0) {
        total += (int)(a % 10);
        a /= 10;
    }

    return x > 0 ? total : total - 2 * first;
}

vector<int> order_by_points(vector<int> nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        int cur = nums[i];
        int cur_sum = point_sum(cur);
        size_t j = i;

        while (j > 0 && point_sum(nums[j - 1]) > cur_sum) {
            nums[j] = nums[j - 1];
            --j;
        }
        nums[j] = cur;
    }
    return nums;
}
