#include <vector>
#include <cmath>
using namespace std;

float mean_absolute_deviation(vector<float> numbers) {
    const size_t n = numbers.size();
    float sum = 0.0f;

    for (float x : numbers) {
        sum += x;
    }

    const float avg = sum / n;
    sum = 0.0f;

    for (float x : numbers) {
        sum += fabsf(x - avg);
    }

    return sum / n;
}
