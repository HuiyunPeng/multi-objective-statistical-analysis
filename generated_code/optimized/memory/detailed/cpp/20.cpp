#include <vector>
#include <cmath>
using namespace std;

vector<float> find_closest_elements(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n < 2) return {};

    float first = numbers[0];
    float second = numbers[1];
    float best_diff = fabsf(first - second);

    for (size_t i = 0; i + 1 < n; ++i) {
        const float ni = numbers[i];
        for (size_t j = i + 1; j < n; ++j) {
            const float diff = fabsf(ni - numbers[j]);
            if (diff < best_diff) {
                best_diff = diff;
                first = ni;
                second = numbers[j];
            }
        }
    }

    vector<float> out(2);
    if (first <= second) {
        out[0] = first;
        out[1] = second;
    } else {
        out[0] = second;
        out[1] = first;
    }
    return out;
}
