#include <vector>
using namespace std;

int smallest_change(vector<int> arr) {
    int out = 0;
    const int n = static_cast<int>(arr.size());
    if (n < 2) return 0;

    const int* left = arr.data();
    const int* right = left + n - 1;

    while (left < right) {
        out += (*left++ != *right--);
    }

    return out;
}
