#include <vector>
#include <algorithm>
using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    const int n = static_cast<int>(lst.size());
    if (n <= 1) return lst;

    sort(lst.begin(), lst.end());

    vector<int> out(n);
    int l = 0, r = n - 1, i = 0;

    while (l < r) {
        out[i++] = lst[l++];
        out[i++] = lst[r--];
    }
    if (l == r) out[i] = lst[l];

    return out;
}
