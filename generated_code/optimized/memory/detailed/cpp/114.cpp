#include <vector>

long long minSubArraySum(std::vector<long long> nums) {
    long long current = nums[0];
    long long min_sum = nums[0];

    for (std::size_t i = 1, n = nums.size(); i < n; ++i) {
        current = (current < 0) ? (current + nums[i]) : nums[i];
        if (current < min_sum) {
            min_sum = current;
        }
    }

    return min_sum;
}
