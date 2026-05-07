#include <vector>

int sum_squares(std::vector<int> lst) {
    int sum = 0;
    const int* data = lst.data();
    const std::size_t n = lst.size();

    for (std::size_t i = 0; i < n; ++i) {
        const int x = data[i];
        if (i % 3 == 0) {
            sum += x * x;
        } else if (i % 4 == 0) {
            sum += x * x * x;
        } else {
            sum += x;
        }
    }

    return sum;
}
