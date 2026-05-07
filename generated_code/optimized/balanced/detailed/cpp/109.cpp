#include <vector>
using namespace std;

bool move_one_ball(vector<int> arr) {
    const size_t n = arr.size();
    if (n < 2) return true;

    const int* p = arr.data();
    int drops = 0;

    for (size_t i = 1; i < n; ++i) {
        if (p[i] < p[i - 1] && ++drops >= 2) return false;
    }

    if (p[n - 1] > p[0] && ++drops >= 2) return false;

    return true;
}
