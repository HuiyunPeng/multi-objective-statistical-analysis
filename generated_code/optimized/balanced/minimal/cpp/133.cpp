#include <vector>
#include <cmath>

using std::vector;

int sum_squares(vector<float> lst) {
    int sum = 0;
    const float* p = lst.data();
    const float* end = p + lst.size();

    while (p != end) {
        const float c = std::ceil(*p++);
        sum += static_cast<int>(c * c);
    }

    return sum;
}
