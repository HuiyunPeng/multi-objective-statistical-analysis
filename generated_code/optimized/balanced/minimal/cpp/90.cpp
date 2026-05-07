#include <vector>
using namespace std;

int next_smallest(vector<int> lst) {
    int smallest = 0, second = 0;
    bool hasSmallest = false, hasSecond = false;

    for (int x : lst) {
        if (!hasSmallest || x < smallest) {
            if (hasSmallest && x != smallest) {
                second = smallest;
                hasSecond = true;
            }
            smallest = x;
            hasSmallest = true;
        } else if (x != smallest && (!hasSecond || x < second)) {
            second = x;
            hasSecond = true;
        }
    }

    return hasSecond ? second : -1;
}
