#include <vector>
#include <cmath>

using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    const float* data = numbers.data();

    float sum = 0.0f;
    const float* p = data;
    const float* end = data + n;
    while (p != end) {
        sum += *p++;
    }

    const float avg = sum / static_cast<float>(n);

    float msum = 0.0f;
    p = data;
    while (p != end) {
        msum += fabsf(*p++ - avg);
    }

    return msum / static_cast<float>(n);
}
