#include <vector>
#include <algorithm>
using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    const size_t n = lst.size();
    if (n == 0) return {};

    sort(lst.begin(), lst.end());

    vector<int> out(n);
    size_t l = 0, r = n - 1, i = 0;

    while (l < r) {
        out[i++] = lst[l++];
        out[i++] = lst[r--];
    }
    if (l == r) out[i] = lst[l];

    return out;
}
