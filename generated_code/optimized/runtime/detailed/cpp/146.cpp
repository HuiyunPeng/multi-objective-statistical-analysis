#include <vector>
using namespace std;

int specialFilter(vector<int> nums) {
    int count = 0;
    const int n = static_cast<int>(nums.size());

    for (int i = 0; i < n; ++i) {
        int x = nums[i];
        if (x <= 10 || !(x & 1)) continue;  // must be > 10 and end with an odd digit

        while (x >= 10) x /= 10;            // extract first digit
        count += (x & 1);                   // first digit is odd
    }

    return count;
}
