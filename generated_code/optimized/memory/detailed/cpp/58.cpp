#include <vector>
#include <algorithm>
using namespace std;

vector<int> common(vector<int> l1, vector<int> l2) {
    if (l1.empty() || l2.empty()) {
        return {};
    }

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    size_t i = 0, j = 0, k = 0;

    while (i < l1.size() && j < l2.size()) {
        if (l1[i] < l2[j]) {
            int v = l1[i];
            while (i < l1.size() && l1[i] == v) ++i;
        } else if (l2[j] < l1[i]) {
            int v = l2[j];
            while (j < l2.size() && l2[j] == v) ++j;
        } else {
            int v = l1[i];
            l1[k++] = v;
            while (i < l1.size() && l1[i] == v) ++i;
            while (j < l2.size() && l2[j] == v) ++j;
        }
    }

    l1.resize(k);
    return l1;
}
