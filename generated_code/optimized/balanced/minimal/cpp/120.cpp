#include <vector>
#include <algorithm>
using namespace std;

vector<int> maximum(vector<int> arr, int k) {
    const int n = static_cast<int>(arr.size());
    if (k <= 0) return {};
    if (k >= n) {
        sort(arr.begin(), arr.end());
        return arr;
    }

    auto mid = arr.end() - k;
    nth_element(arr.begin(), mid, arr.end());
    sort(mid, arr.end());

    return vector<int>(mid, arr.end());
}
