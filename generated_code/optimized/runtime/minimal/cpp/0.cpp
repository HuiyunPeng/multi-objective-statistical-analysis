#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool has_close_elements(vector<float> numbers, float threshold) {
    if (threshold <= 0.0f || numbers.size() < 2) {
        return false;
    }

    auto valid_end = remove_if(numbers.begin(), numbers.end(),
                               [](float x) { return std::isnan(x); });

    if (valid_end - numbers.begin() < 2) {
        return false;
    }

    sort(numbers.begin(), valid_end);

    for (auto it = numbers.begin() + 1; it != valid_end; ++it) {
        if (fabsf(*it - *(it - 1)) < threshold) {
            return true;
        }
    }

    return false;
}
