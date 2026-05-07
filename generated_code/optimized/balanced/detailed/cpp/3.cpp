#include <vector>

bool below_zero(std::vector<int> operations) {
    int sum = 0;
    const int* p = operations.data();
    const int* end = p + operations.size();

    while (p != end) {
        sum += *p++;
        if (sum < 0) return true;
    }

    return false;
}
