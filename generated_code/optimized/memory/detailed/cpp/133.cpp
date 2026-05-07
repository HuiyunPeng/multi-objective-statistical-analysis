#include <vector>
#include <cmath>

int sum_squares(std::vector<float> lst) {
    int sum = 0;
    const std::size_t n = lst.size();
    for (std::size_t i = 0; i < n; ++i) {
        const double c = std::ceil(lst[i]);
        sum += static_cast<int>(c * c);
    }
    return sum;
}
