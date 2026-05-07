#include <vector>
using namespace std;

vector<int> pluck(vector<int> arr) {
    int bestIdx = -1;
    int bestVal = 0;
    const int n = static_cast<int>(arr.size());

    for (int i = 0; i < n; ++i) {
        const int x = arr[i];
        if (x % 2 == 0 && (bestIdx == -1 || x < bestVal)) {
            bestVal = x;
            bestIdx = i;
        }
    }

    if (bestIdx == -1) return {};
    return {bestVal, bestIdx};
}
