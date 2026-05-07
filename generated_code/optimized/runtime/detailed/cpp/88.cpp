#include <vector>
#include <algorithm>
using namespace std;

vector<int> sort_array(vector<int> array) {
    if (array.empty()) return {};

    const bool reverse_order = ((array.front() + array.back()) % 2) != 1;

    sort(array.begin(), array.end());

    if (reverse_order) {
        reverse(array.begin(), array.end());
    }

    return array;
}
