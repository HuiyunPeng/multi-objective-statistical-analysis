#include <vector>
#include <cmath>

using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n == 0) {
        return 0.0f;
    }

    const float inv_n = 1.0f / static_cast<float>(n);

    const float* data = numbers.data();
    const float* end = data + n;

    float sum = 0.0f;
    for (const float* p = data; p != end; ++p) {
        sum += *p;
    }

    const float avg = sum * inv_n;

    float msum = 0.0f;
    for (const float* p = data; p != end; ++p) {
        msum += std::fabs(*p - avg);
    }

    return msum * inv_n;
}
