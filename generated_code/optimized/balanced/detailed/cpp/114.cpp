#include <vector>

long long minSubArraySum(std::vector<long long> nums) {
    const size_t n = nums.size();
    if (n == 0) return 0;

    const long long* data = nums.data();
    long long current = data[0];
    long long best = data[0];

    for (size_t i = 1; i < n; ++i) {
        const long long x = data[i];
        current = (current < 0) ? (current + x) : x;
        if (current < best) best = current;
    }

    return best;
}
