#include <vector>
using namespace std;

int smallest_change(vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return 0;

    const int* data = arr.data();
    int out = 0;
    size_t i = 0, j = n - 1;

    while (i < j) {
        out += (data[i] != data[j]);
        ++i;
        --j;
    }

    return out;
}
