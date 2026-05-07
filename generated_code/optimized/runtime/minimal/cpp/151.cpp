#include <vector>
#include <cmath>
using namespace std;

long long double_the_difference(vector<float> lst) {
    long long sum = 0;
    const size_t n = lst.size();

    for (size_t i = 0; i < n; ++i) {
        const float x = lst[i];
        const float r = roundf(x);

        if (x - r < 1e-4f && x > 0.0f) {
            const int ri = (int)r;
            if (ri & 1) {
                sum += 1LL * ri * ri;
            }
        }
    }

    return sum;
}
