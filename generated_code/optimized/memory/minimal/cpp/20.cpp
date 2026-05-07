#include <vector>
#include <cmath>

using namespace std;

vector<float> find_closest_elements(vector<float> numbers) {
    float a = numbers[0], b = numbers[1];
    float best = fabs(numbers[0] - numbers[1]);

    for (size_t i = 0; i + 1 < numbers.size(); ++i) {
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            float diff = fabs(numbers[i] - numbers[j]);
            if (diff < best) {
                best = diff;
                a = numbers[i];
                b = numbers[j];
            }
        }
    }

    if (a > b) {
        float t = a;
        a = b;
        b = t;
    }

    vector<float> out(2);
    out[0] = a;
    out[1] = b;
    return out;
}
