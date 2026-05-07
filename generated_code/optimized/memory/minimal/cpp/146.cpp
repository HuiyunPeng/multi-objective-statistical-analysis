#include <vector>
using namespace std;

int specialFilter(vector<int> nums) {
    int count = 0;
    for (int x : nums) {
        if (x > 10 && (x % 10) & 1) {
            int first = x;
            while (first >= 10) first /= 10;
            if (first & 1) ++count;
        }
    }
    return count;
}
