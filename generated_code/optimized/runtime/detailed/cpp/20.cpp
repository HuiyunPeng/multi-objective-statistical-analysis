#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<float> find_closest_elements(vector<float> numbers) {
    const int n = static_cast<int>(numbers.size());
    if (n < 2) return {};

    sort(numbers.begin(), numbers.end());

    float a = numbers[0], b = numbers[1];
    float best_diff = b - a;

    for (int i = 1; i < n - 1; ++i) {
        const float diff = numbers[i + 1] - numbers[i];
        if (diff < best_diff) {
            best_diff = diff;
            a = numbers[i];
            b = numbers[i + 1];
        }
    }

    return {a, b};
}
