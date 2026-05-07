#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool has_close_elements(vector<float> numbers, float threshold) {
    const size_t n = numbers.size();
    if (n < 2) return false;

    sort(numbers.begin(), numbers.end());

    for (size_t i = 1; i < n; ++i) {
        if (numbers[i] - numbers[i - 1] < threshold) {
            return true;
        }
    }

    return false;
}
