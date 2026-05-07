#include <vector>
#include <cmath>

using std::vector;

int sum_squares(vector<float> lst) {
    int sum = 0;
    const float* p = lst.data();
    const float* end = p + lst.size();

    for (; p != end; ++p) {
        const int c = static_cast<int>(std::ceil(*p));
        sum += c * c;
    }

    return sum;
}
