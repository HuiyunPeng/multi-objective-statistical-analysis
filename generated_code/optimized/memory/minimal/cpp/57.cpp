#include <vector>
using namespace std;

bool monotonic(vector<float> l) {
    bool incr = false, decr = false;
    for (size_t i = 1, n = l.size(); i < n; ++i) {
        if (l[i] > l[i - 1]) incr = true;
        else if (l[i] < l[i - 1]) decr = true;
        if (incr && decr) return false;
    }
    return true;
}
