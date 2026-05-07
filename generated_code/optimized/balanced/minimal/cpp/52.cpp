#include <vector>

bool below_threshold(std::vector<int> l, int t) {
    const int* p = l.data();
    const int* end = p + l.size();
    while (p != end) {
        if (*p >= t) return false;
        ++p;
    }
    return true;
}
