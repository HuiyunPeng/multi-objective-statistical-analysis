#include <vector>
using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    if (numbers.empty()) return numbers;

    float min_val = numbers[0];
    float max_val = numbers[0];

    for (size_t i = 1; i < numbers.size(); ++i) {
        const float v = numbers[i];
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }

    const float range = max_val - min_val;
    if (range == 0.0f) {
        for (size_t i = 0; i < numbers.size(); ++i) {
            numbers[i] = 0.0f;
        }
        return numbers;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        numbers[i] = (numbers[i] - min_val) / range;
    }

    return numbers;
}
