#include <vector>
using namespace std;

vector<float> derivative(vector<float> xs) {
    const size_t n = xs.size();
    if (n <= 1) return {};

    vector<float> out(n - 1);
    for (size_t i = 1; i < n; ++i) {
        out[i - 1] = static_cast<float>(i) * xs[i];
    }
    return out;
}
