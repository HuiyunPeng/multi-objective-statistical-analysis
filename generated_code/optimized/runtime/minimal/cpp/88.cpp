#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

vector<int> sort_array(vector<int> array) {
    if (array.empty()) return {};
    if (((array.front() + array.back()) & 1) != 0)
        sort(array.begin(), array.end());
    else
        sort(array.begin(), array.end(), greater<int>());
    return array;
}
