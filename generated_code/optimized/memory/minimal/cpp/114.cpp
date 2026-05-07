#include <vector>
using namespace std;

long long minSubArraySum(vector<long long> nums) {
    long long current = nums[0];
    long long best = nums[0];

    for (size_t i = 1; i < nums.size(); ++i) {
        current = (current < 0) ? (current + nums[i]) : nums[i];
        if (current < best) best = current;
    }

    return best;
}
