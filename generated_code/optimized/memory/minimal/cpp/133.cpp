#include <vector>
#include <cmath>

int sum_squares(std::vector<float> lst) {
    int sum = 0;
    for (float x : lst) {
        int c = static_cast<int>(std::ceil(x));
        sum += c * c;
    }
    return sum;
}
