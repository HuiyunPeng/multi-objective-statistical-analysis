#include <vector>
using namespace std;

vector<int> pluck(vector<int> arr) {
    const int n = static_cast<int>(arr.size());
    int bestIdx = -1;
    int bestVal = 0;

    for (int i = 0; i < n; ++i) {
        const int v = arr[i];
        if (v % 2 == 0 && (bestIdx == -1 || v < bestVal)) {
            bestVal = v;
            bestIdx = i;
        }
    }

    if (bestIdx == -1) return {};
    return {bestVal, bestIdx};
}
