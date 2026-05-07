#include <vector>
using namespace std;

bool monotonic(vector<float> l) {
    const size_t n = l.size();
    if (n < 2) return true;

    int trend = 0; // 1: increasing seen, -1: decreasing seen
    const float* p = l.data();

    for (size_t i = 1; i < n; ++i) {
        if (p[i] > p[i - 1]) {
            if (trend < 0) return false;
            trend = 1;
        } else if (p[i] < p[i - 1]) {
            if (trend > 0) return false;
            trend = -1;
        }
    }

    return true;
}
