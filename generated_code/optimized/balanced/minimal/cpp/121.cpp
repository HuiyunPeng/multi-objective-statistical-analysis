#include <vector>
#include <cstddef>

using std::vector;

int solutions(vector<int> lst) {
    int sum = 0;
    const std::size_t n = lst.size();

    for (std::size_t i = 0; i < n; i += 2) {
        const int v = lst[i];
        if (v & 1) sum += v;
    }

    return sum;
}
