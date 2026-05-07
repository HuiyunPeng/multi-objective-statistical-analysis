#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> array) {
    if (array.empty()) return array;

    const bool descending = ((array.front() ^ array.back()) & 1) == 0;

    sort(array.begin(), array.end());
    if (descending) {
        reverse(array.begin(), array.end());
    }

    return array;
}
