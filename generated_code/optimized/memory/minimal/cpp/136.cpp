#include <vector>
using namespace std;

vector<int> largest_smallest_integers(vector<int> lst) {
    int maxneg = 0, minpos = 0;
    for (int x : lst) {
        if (x < 0 && (maxneg == 0 || x > maxneg)) maxneg = x;
        else if (x > 0 && (minpos == 0 || x < minpos)) minpos = x;
    }
    vector<int> result(2);
    result[0] = maxneg;
    result[1] = minpos;
    return result;
}
