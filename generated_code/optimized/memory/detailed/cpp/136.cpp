#include <vector>
using namespace std;

vector<int> largest_smallest_integers(vector<int> lst) {
    int maxneg = 0, minpos = 0;

    for (int x : lst) {
        if (x < 0) {
            if (maxneg == 0 || x > maxneg) maxneg = x;
        } else if (x > 0) {
            if (minpos == 0 || x < minpos) minpos = x;
        }
    }

    if (lst.size() < 2) lst.resize(2);
    lst[0] = maxneg;
    lst[1] = minpos;
    lst.resize(2);

    return lst;
}
