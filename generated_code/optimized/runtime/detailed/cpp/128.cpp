#include <vector>

int prod_signs(std::vector<int> arr) {
    const size_t n = arr.size();
    if (n == 0) return -32768;

    int sum = 0;
    int prods = 1;

    const int* p = arr.data();
    const int* end = p + n;

    while (p != end) {
        const int x = *p++;
        if (x < 0) {
            sum -= x;
            prods = -prods;
        } else {
            sum += x;
            if (x == 0) prods = 0;
        }
    }

    return sum * prods;
}
