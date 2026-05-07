#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include <stdlib.h>

static inline int digit_score(int x) {
    if (x == 0) return 0;

    long long v = x;
    if (v < 0) v = -v;

    int sum = 0;
    long long t = v;
    while (t > 0) {
        sum += (int)(t % 10);
        t /= 10;
    }

    long long msd = v;
    while (msd >= 10) msd /= 10;

    return x > 0 ? sum : sum - 2 * (int)msd;
}

vector<int> order_by_points(vector<int> nums) {
    for (int i = 1; i < (int)nums.size(); ++i) {
        int value = nums[i];
        int value_score = digit_score(value);
        int j = i - 1;

        while (j >= 0 && digit_score(nums[j]) > value_score) {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = value;
    }
    return nums;
}
