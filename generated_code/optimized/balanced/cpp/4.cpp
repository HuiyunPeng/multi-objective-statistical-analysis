#include <vector>
#include <cmath>
#include <cstddef>
using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) return 0.0f;

    const float* p = numbers.data();
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) sum += p[i];

    const float mean = static_cast<float>(sum / n);

    double dev_sum = 0.0;
    for (size_t i = 0; i < n; ++i) dev_sum += std::fabs(p[i] - mean);

    return static_cast<float>(dev_sum / n);
}
