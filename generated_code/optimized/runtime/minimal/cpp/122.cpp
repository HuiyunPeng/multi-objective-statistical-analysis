#include <vector>

int add_elements(std::vector<int> arr, int k) {
    if (k <= 0) return 0;

    int sum = 0;
    const int* data = arr.data();

    int i = 0;
    const int limit = k & ~3;

    for (; i < limit; i += 4) {
        int x0 = data[i];
        if (x0 >= -99 && x0 <= 99) sum += x0;

        int x1 = data[i + 1];
        if (x1 >= -99 && x1 <= 99) sum += x1;

        int x2 = data[i + 2];
        if (x2 >= -99 && x2 <= 99) sum += x2;

        int x3 = data[i + 3];
        if (x3 >= -99 && x3 <= 99) sum += x3;
    }

    for (; i < k; ++i) {
        int x = data[i];
        if (x >= -99 && x <= 99) sum += x;
    }

    return sum;
}
