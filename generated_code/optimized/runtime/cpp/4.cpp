#include <vector>
#include <cmath>
using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    const float* p = numbers.data();

    float sum = 0.0f;
    for (size_t i = 0; i < n; ++i) sum += p[i];

    const float avg = sum / static_cast<float>(n);

    float msum = 0.0f;
    for (size_t i = 0; i < n; ++i) msum += fabsf(p[i] - avg);

    return msum / static_cast<float>(n);
}
