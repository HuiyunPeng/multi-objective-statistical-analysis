#include <vector>
using namespace std;

bool monotonic(vector<float> l) {
    bool incr = false, decr = false;
    const size_t n = l.size();

    for (size_t i = 1; i < n; ++i) {
        if (l[i] > l[i - 1]) {
            incr = true;
        } else if (l[i] < l[i - 1]) {
            decr = true;
        }

        if (incr && decr) return false;
    }

    return true;
}
