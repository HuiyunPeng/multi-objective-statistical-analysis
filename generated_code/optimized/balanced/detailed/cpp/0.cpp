#include <vector>
#include <algorithm>

using namespace std;

bool has_close_elements(vector<float> numbers, float threshold) {
    const size_t n = numbers.size();
    if (n < 2 || threshold <= 0.0f) return false;

    sort(numbers.begin(), numbers.end());

    for (size_t i = 1; i < n; ++i) {
        if (numbers[i] - numbers[i - 1] < threshold) {
            return true;
        }
    }

    return false;
}
