#include <vector>
using namespace std;

int specialFilter(vector<int> nums) {
    int count = 0;
    for (int x : nums) {
        if (x > 10) {
            int last = x % 10;
            int first = x;
            while (first >= 10) first /= 10;
            if ((first & 1) && (last & 1)) ++count;
        }
    }
    return count;
}
