#include <vector>
#include <cstdlib>

int prod_signs(std::vector<int> arr) {
    const size_t n = arr.size();
    if (n == 0) return -32768;

    int sum = 0;
    int sign = 1;

    for (size_t i = 0; i < n; ++i) {
        const int v = arr[i];
        sum += std::abs(v);
        if (v == 0) return 0;
        if (v < 0) sign = -sign;
    }

    return sum * sign;
}
