#include <vector>
#include <cmath>
using std::vector;

long long double_the_difference(vector<float> lst) {
    long long sum = 0;
    for (float x : lst) {
        if (!(x > 0.0f)) continue;
        float r = std::round(x);
        if (x - r < 1e-4f) {
            long long n = static_cast<long long>(r);
            if (n & 1LL) sum += n * n;
        }
    }
    return sum;
}
