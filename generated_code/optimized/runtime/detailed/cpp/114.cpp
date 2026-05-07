#include <vector>
using namespace std;

long long minSubArraySum(vector<long long> nums) {
    const long long* p = nums.data();
    const long long* end = p + nums.size();

    long long current = *p;
    long long minVal = *p;
    ++p;

    while (p != end) {
        const long long x = *p++;
        current = (current < 0) ? (current + x) : x;
        if (current < minVal) minVal = current;
    }

    return minVal;
}
