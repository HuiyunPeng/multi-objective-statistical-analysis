#include <vector>
using std::vector;

int can_arrange(vector<int> arr) {
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        if (arr[i] <= i) {
            return i;
        }
    }
    return -1;
}
