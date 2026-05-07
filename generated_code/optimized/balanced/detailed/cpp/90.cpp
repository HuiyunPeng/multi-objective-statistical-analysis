#include <vector>
#include <climits>

int next_smallest(std::vector<int> lst) {
    int smallest = INT_MAX;
    int second = INT_MAX;

    for (int x : lst) {
        if (x < smallest) {
            second = smallest;
            smallest = x;
        } else if (x > smallest && x < second) {
            second = x;
        }
    }

    return second == INT_MAX ? -1 : second;
}
