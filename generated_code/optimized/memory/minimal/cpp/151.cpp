#include <vector>
#include <cmath>
using namespace std;

long long double_the_difference(vector<float> lst) {
    long long sum = 0;
    const size_t n = lst.size();

    for (size_t i = 0; i < n; ++i) {
        const float v = lst[i];
        const double r = round(v);

        if (v - r < 1e-4f) {
            const int ri = (int)r;
            if (v > 0 && (ri & 1)) {
                sum += 1LL * ri * ri;
            }
        }
    }

    return sum;
}
