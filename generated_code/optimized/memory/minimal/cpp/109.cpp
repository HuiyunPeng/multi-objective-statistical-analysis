#include <vector>
using namespace std;

bool move_one_ball(vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return true;

    int drops = 0;
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1] && ++drops >= 2) return false;
    }
    if (arr[n - 1] > arr[0] && ++drops >= 2) return false;

    return true;
}
