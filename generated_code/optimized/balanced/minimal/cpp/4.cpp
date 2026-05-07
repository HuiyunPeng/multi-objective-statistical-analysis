#include <vector>
#include <cmath>

using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) return 0.0f;

    const float* data = numbers.data();

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += data[i];
    }

    const double avg = sum / static_cast<double>(n);

    double dev_sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        dev_sum += std::fabs(static_cast<double>(data[i]) - avg);
    }

    return static_cast<float>(dev_sum / static_cast<double>(n));
}
