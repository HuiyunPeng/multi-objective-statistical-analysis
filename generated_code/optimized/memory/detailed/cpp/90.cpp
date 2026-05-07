#include <vector>
#include <limits>
using namespace std;

int next_smallest(vector<int> lst) {
    int smallest = numeric_limits<int>::max();
    int second = numeric_limits<int>::max();

    for (int x : lst) {
        if (x < smallest) {
            second = smallest;
            smallest = x;
        } else if (x > smallest && x < second) {
            second = x;
        }
    }

    return second == numeric_limits<int>::max() ? -1 : second;
}
