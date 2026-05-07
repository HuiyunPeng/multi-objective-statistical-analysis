#include <vector>
using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) return numbers;

    float* data = numbers.data();
    float min_val = data[0];
    float max_val = data[0];

    for (size_t i = 1; i < n; ++i) {
        const float v = data[i];
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }

    const float range = max_val - min_val;
    if (range == 0.0f) {
        for (size_t i = 0; i < n; ++i) data[i] = 0.0f;
        return numbers;
    }

    const float inv_range = 1.0f / range;
    for (size_t i = 0; i < n; ++i) {
        data[i] = (data[i] - min_val) * inv_range;
    }

    return numbers;
}
