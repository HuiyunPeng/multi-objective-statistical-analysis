#include <vector>

using std::vector;

int smallest_change(vector<int> arr) {
    int out = 0;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left < right) {
        if (arr[left] != arr[right]) {
            ++out;
        }
        ++left;
        --right;
    }

    return out;
}
