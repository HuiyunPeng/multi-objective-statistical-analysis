#include <vector>

std::vector<int> largest_smallest_integers(std::vector<int> lst) {
    int maxneg = 0, minpos = 0;
    bool hasNeg = false, hasPos = false;

    const int* p = lst.data();
    const int* end = p + lst.size();

    for (; p != end; ++p) {
        const int x = *p;
        if (x < 0) {
            if (!hasNeg || x > maxneg) {
                maxneg = x;
                hasNeg = true;
            }
        } else if (x > 0) {
            if (!hasPos || x < minpos) {
                minpos = x;
                hasPos = true;
            }
        }
    }

    return {maxneg, minpos};
}
