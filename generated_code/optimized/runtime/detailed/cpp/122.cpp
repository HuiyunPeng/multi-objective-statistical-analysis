#include <vector>

int add_elements(std::vector<int> arr, int k) {
    int sum = 0;
    const int* p = arr.data();
    const int* end = p + k;

    for (; p != end; ++p) {
        const int v = *p;
        if (static_cast<unsigned>(v + 99) <= 198u) {
            sum += v;
        }
    }

    return sum;
}
