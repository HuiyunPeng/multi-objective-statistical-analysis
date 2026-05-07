#include <vector>
using namespace std;

int specialFilter(vector<int> nums) {
    int count = 0;
    for (int x : nums) {
        if (x <= 10 || (x & 1) == 0) continue;

        while (x >= 10) x /= 10;
        if (x & 1) ++count;
    }
    return count;
}
