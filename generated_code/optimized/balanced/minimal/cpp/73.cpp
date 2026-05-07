#include <vector>
using namespace std;

int smallest_change(vector<int> arr) {
    const size_t n = arr.size();
    const size_t half = n >> 1;
    const int* data = arr.data();

    int out = 0;
    for (size_t i = 0; i < half; ++i) {
        out += (data[i] != data[n - 1 - i]);
    }
    return out;
}
