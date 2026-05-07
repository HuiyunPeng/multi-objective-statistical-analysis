#include <vector>
#include <cmath>

using namespace std;

long long double_the_difference(vector<float> lst) {
    long long sum = 0;

    for (float x : lst) {
        if (x <= 0.0f) continue;

        const float r = roundf(x);
        if (x - r < 1e-4f) {
            const int ri = static_cast<int>(r);
            if (ri & 1) {
                sum += 1LL * ri * ri;
            }
        }
    }

    return sum;
}
