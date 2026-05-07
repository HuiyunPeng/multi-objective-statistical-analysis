#include <vector>

int solutions(std::vector<int> lst) {
    int sum = 0;
    const int n = static_cast<int>(lst.size());
    for (int i = 0; i < n; i += 2) {
        const int x = lst[i];
        if (x & 1) sum += x;
    }
    return sum;
}
