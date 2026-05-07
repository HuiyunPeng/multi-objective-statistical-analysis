#include <vector>

std::vector<int> largest_smallest_integers(std::vector<int> lst) {
    int maxneg = 0, minpos = 0;
    for (int x : lst) {
        if (x < 0) {
            if (maxneg == 0 || x > maxneg) maxneg = x;
        } else if (x > 0) {
            if (minpos == 0 || x < minpos) minpos = x;
        }
    }
    return {maxneg, minpos};
}
