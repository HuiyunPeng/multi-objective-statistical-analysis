#include <vector>
using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) return numbers;

    float* data = numbers.data();
    float mn = data[0];
    float mx = data[0];

    for (size_t i = 1; i < n; ++i) {
        const float v = data[i];
        if (v < mn) mn = v;
        if (v > mx) mx = v;
    }

    const float invRange = 1.0f / (mx - mn);
    for (size_t i = 0; i < n; ++i) {
        data[i] = (data[i] - mn) * invRange;
    }

    return numbers;
}
