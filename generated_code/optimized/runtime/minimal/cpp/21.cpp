#include <vector>
using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) return numbers;

    float* data = numbers.data();
    float minv = data[0];
    float maxv = data[0];

    for (size_t i = 1; i < n; ++i) {
        const float x = data[i];
        if (x < minv) minv = x;
        if (x > maxv) maxv = x;
    }

    const float invRange = 1.0f / (maxv - minv);
    for (size_t i = 0; i < n; ++i) {
        data[i] = (data[i] - minv) * invRange;
    }

    return numbers;
}
