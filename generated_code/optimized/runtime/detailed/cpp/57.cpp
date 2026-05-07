#include <vector>
using namespace std;

bool monotonic(vector<float> l) {
    const size_t n = l.size();
    if (n < 2) return true;

    bool incr = false, decr = false;
    float prev = l[0];

    for (size_t i = 1; i < n; ++i) {
        const float curr = l[i];
        if (curr > prev) {
            incr = true;
            if (decr) return false;
        } else if (curr < prev) {
            decr = true;
            if (incr) return false;
        }
        prev = curr;
    }

    return true;
}
