#include <vector>
#include <cmath>
using namespace std;

long long double_the_difference(vector<float> lst) {
    long long sum = 0;
    const size_t n = lst.size();
    const float* data = lst.data();
    const float eps = 1e-4f;

    for (size_t i = 0; i < n; ++i) {
        const float x = data[i];
        if (x <= 0.0f) continue;

        const float r = std::round(x);
        if (x - r < eps) {
            const int ri = static_cast<int>(r);
            if (ri & 1) {
                sum += 1LL * ri * ri;
            }
        }
    }

    return sum;
}
