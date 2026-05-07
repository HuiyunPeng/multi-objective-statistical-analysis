#include <vector>
using namespace std;

int smallest_change(vector<int> arr) {
    int out = 0;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left < right) {
        out += (arr[left] != arr[right]);
        ++left;
        --right;
    }

    return out;
}
