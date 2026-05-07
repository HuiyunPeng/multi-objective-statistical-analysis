#include <vector>
using namespace std;

vector<int> pluck(vector<int> arr) {
    const size_t n = arr.size();
    int bestValue = 0;
    int bestIndex = -1;

    for (size_t i = 0; i < n; ++i) {
        const int v = arr[i];
        if (v % 2 == 0 && (bestIndex == -1 || v < bestValue)) {
            bestValue = v;
            bestIndex = static_cast<int>(i);
        }
    }

    if (bestIndex == -1) return {};
    return {bestValue, bestIndex};
}
