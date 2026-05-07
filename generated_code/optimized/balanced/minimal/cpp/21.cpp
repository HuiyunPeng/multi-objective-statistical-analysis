#include <vector>
#include <algorithm>

using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    if (numbers.empty()) return numbers;

    auto mm = minmax_element(numbers.begin(), numbers.end());
    const float min_val = *mm.first;
    const float max_val = *mm.second;
    const float range = max_val - min_val;

    if (range == 0.0f) {
        fill(numbers.begin(), numbers.end(), 0.0f);
        return numbers;
    }

    const float inv_range = 1.0f / range;
    for (float& x : numbers) {
        x = (x - min_val) * inv_range;
    }

    return numbers;
}
