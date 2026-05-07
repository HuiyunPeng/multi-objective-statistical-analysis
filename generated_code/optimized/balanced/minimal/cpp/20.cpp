#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<float> find_closest_elements(vector<float> numbers) {
    if (numbers.size() < 2) return {};

    sort(numbers.begin(), numbers.end());

    float a = numbers[0], b = numbers[1];
    float best_diff = b - a;

    for (size_t i = 2; i < numbers.size(); ++i) {
        float diff = numbers[i] - numbers[i - 1];
        if (diff < best_diff) {
            best_diff = diff;
            a = numbers[i - 1];
            b = numbers[i];
        }
    }

    return {a, b};
}
