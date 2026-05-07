#include <vector>
#include <cstdlib>

using std::vector;

int prod_signs(vector<int> arr) {
    const auto n = arr.size();
    if (n == 0) return -32768;

    int sum = 0;
    bool negative = false;

    const int* p = arr.data();
    const int* end = p + n;

    for (; p != end; ++p) {
        const int x = *p;
        if (x == 0) return 0;
        sum += std::abs(x);
        negative ^= (x < 0);
    }

    return negative ? -sum : sum;
}
