#include <vector>
#include <algorithm>

using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    const int n = static_cast<int>(lst.size());
    if (n < 2) return lst;

    sort(lst.begin(), lst.end());

    vector<int> out;
    out.reserve(n);

    int l = 0, r = n - 1;
    while (l < r) {
        out.push_back(lst[l++]);
        out.push_back(lst[r--]);
    }
    if (l == r) out.push_back(lst[l]);

    return out;
}
