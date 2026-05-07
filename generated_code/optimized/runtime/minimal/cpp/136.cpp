#include <vector>
using namespace std;

vector<int> largest_smallest_integers(vector<int> lst) {
    int maxneg = 0, minpos = 0;
    const int* p = lst.data();
    const int* end = p + lst.size();

    while (p != end) {
        const int x = *p++;
        if (x < 0) {
            if (maxneg == 0 || x > maxneg) maxneg = x;
        } else if (x > 0) {
            if (minpos == 0 || x < minpos) minpos = x;
        }
    }

    return {maxneg, minpos};
}
