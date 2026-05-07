#include <vector>
#include <algorithm>

using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    sort(lst.begin(), lst.end());
    const size_t n = lst.size();
    if (n < 2) return lst;

    vector<int> out(n);
    size_t l = 0, r = n, i = 0;

    while (l < r) {
        out[i++] = lst[l++];
        if (l < r) out[i++] = lst[--r];
    }

    return out;
}
