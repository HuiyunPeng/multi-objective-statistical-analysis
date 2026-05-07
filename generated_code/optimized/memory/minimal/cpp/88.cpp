#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> array) {
    if (array.empty()) return array;

    sort(array.begin(), array.end());

    if (((array.front() + array.back()) & 1) == 0) {
        reverse(array.begin(), array.end());
    }

    return array;
}
