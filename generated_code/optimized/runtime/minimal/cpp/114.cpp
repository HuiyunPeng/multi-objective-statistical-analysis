#include <vector>
using namespace std;

long long minSubArraySum(vector<long long> nums) {
    const long long* p = nums.data();
    const long long* end = p + nums.size();

    long long current = *p;
    long long best = *p;

    while (++p != end) {
        current = (current < 0) ? (current + *p) : *p;
        if (current < best) best = current;
    }

    return best;
}
