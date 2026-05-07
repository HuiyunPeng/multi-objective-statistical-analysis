#include <vector>
#include <climits>
using namespace std;

int next_smallest(vector<int> lst) {
    if (lst.size() < 2) return -1;

    int smallest = INT_MAX;
    int second_smallest = INT_MAX;

    for (int x : lst) {
        if (x < smallest) {
            second_smallest = smallest;
            smallest = x;
        } else if (x > smallest && x < second_smallest) {
            second_smallest = x;
        }
    }

    return second_smallest == INT_MAX ? -1 : second_smallest;
}
