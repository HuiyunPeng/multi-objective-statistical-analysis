#include <vector>
#include <algorithm>
using namespace std;

vector<int> maximum(vector<int> arr, int k) {
    if (k <= 0) return {};
    if (k >= (int)arr.size()) {
        sort(arr.begin(), arr.end());
        return arr;
    }

    auto split = arr.end() - k;
    nth_element(arr.begin(), split, arr.end());
    sort(split, arr.end());
    arr.erase(arr.begin(), split);
    return arr;
}
