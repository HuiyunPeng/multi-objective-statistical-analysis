#include <vector>
using namespace std;

bool move_one_ball(vector<int> arr) {
    const int n = static_cast<int>(arr.size());
    if (n < 2) return true;

    int breaks = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1] && ++breaks > 1) return false;
    }

    if (arr[n - 1] > arr[0] && ++breaks > 1) return false;
    return true;
}
