#include <vector>

long long minSubArraySum(std::vector<long long> nums) {
    const long long* p = nums.data();
    const long long* end = p + nums.size();

    long long current = *p;
    long long best = *p;

    for (++p; p != end; ++p) {
        current = (current < 0) ? (current + *p) : *p;
        if (current < best) best = current;
    }

    return best;
}
