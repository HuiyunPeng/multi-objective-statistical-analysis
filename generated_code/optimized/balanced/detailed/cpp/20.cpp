#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<float> find_closest_elements(vector<float> numbers) {
    const size_t n = numbers.size();
    if (n < 2) return {};

    sort(numbers.begin(), numbers.end());

    size_t best_idx = 0;
    float best_diff = fabs(numbers[1] - numbers[0]);

    for (size_t i = 1; i + 1 < n; ++i) {
        const float diff = numbers[i + 1] - numbers[i];
        if (diff < best_diff) {
            best_diff = diff;
            best_idx = i;
        }
    }

    return {numbers[best_idx], numbers[best_idx + 1]};
}
