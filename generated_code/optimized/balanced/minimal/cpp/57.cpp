#include <vector>
using namespace std;

bool monotonic(vector<float> l) {
    const size_t n = l.size();
    if (n < 2) return true;

    const float* p = l.data();
    bool incr = false, decr = false;

    for (size_t i = 1; i < n; ++i) {
        const float curr = p[i];
        const float prev = p[i - 1];

        if (curr > prev) {
            incr = true;
            if (decr) return false;
        } else if (curr < prev) {
            decr = true;
            if (incr) return false;
        }
    }

    return true;
}
