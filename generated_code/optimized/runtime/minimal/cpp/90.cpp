#include <vector>
using namespace std;

int next_smallest(vector<int> lst) {
    if (lst.size() < 2) return -1;

    int smallest = lst[0];
    int second = 0;
    bool hasSecond = false;

    for (size_t i = 1; i < lst.size(); ++i) {
        int x = lst[i];
        if (x < smallest) {
            second = smallest;
            smallest = x;
            hasSecond = true;
        } else if (x != smallest && (!hasSecond || x < second)) {
            second = x;
            hasSecond = true;
        }
    }

    return hasSecond ? second : -1;
}
