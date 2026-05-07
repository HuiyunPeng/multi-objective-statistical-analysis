#include <vector>
using namespace std;

vector<int> pluck(vector<int> arr) {
    int bestValue = 0;
    int bestIndex = -1;
    const int n = static_cast<int>(arr.size());

    for (int i = 0; i < n; ++i) {
        const int v = arr[i];
        if (v % 2 == 0 && (bestIndex == -1 || v < bestValue)) {
            bestValue = v;
            bestIndex = i;
        }
    }

    if (bestIndex == -1) return {};
    return {bestValue, bestIndex};
}
