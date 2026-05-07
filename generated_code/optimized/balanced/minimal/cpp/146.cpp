#include <vector>
using namespace std;

int specialFilter(vector<int> nums) {
    int count = 0;

    for (int x : nums) {
        if (x <= 10 || ((x % 10) & 1) == 0) {
            continue;
        }

        while (x >= 100) {
            x /= 100;
        }
        if (x >= 10) {
            x /= 10;
        }

        count += (x & 1);
    }

    return count;
}
