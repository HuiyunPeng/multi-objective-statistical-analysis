#include <vector>
#include <cmath>

using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    float sum = 0.0f;

    for (float x : numbers) {
        sum += x;
    }

    const float avg = sum / static_cast<float>(n);
    float msum = 0.0f;

    for (float x : numbers) {
        msum += fabsf(x - avg);
    }

    return msum / static_cast<float>(n);
}
