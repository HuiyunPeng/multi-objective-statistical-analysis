#include <vector>
#include <algorithm>
using namespace std;

vector<int> maximum(vector<int> arr, int k) {
    if (k <= 0 || arr.empty()) {
        return {};
    }

    const size_t n = arr.size();
    if (static_cast<size_t>(k) >= n) {
        sort(arr.begin(), arr.end());
        return arr;
    }

    auto mid = arr.end() - k;
    nth_element(arr.begin(), mid, arr.end());
    sort(mid, arr.end());

    return vector<int>(mid, arr.end());
}
