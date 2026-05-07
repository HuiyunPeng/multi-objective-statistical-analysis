#include <vector>
using namespace std;

vector<float> derivative(vector<float> xs) {
    const size_t n = xs.size();
    if (n == 0) return xs;

    for (size_t i = 1; i < n; ++i)
        xs[i - 1] = static_cast<float>(i) * xs[i];

    xs.resize(n - 1);
    return xs;
}
