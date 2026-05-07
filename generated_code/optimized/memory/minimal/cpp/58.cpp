#include <vector>
#include <algorithm>
using namespace std;

vector<int> common(vector<int> l1, vector<int> l2) {
    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    vector<int> out;
    size_t i = 0, j = 0;

    while (i < l1.size() && j < l2.size()) {
        if (l1[i] < l2[j]) {
            ++i;
        } else if (l2[j] < l1[i]) {
            ++j;
        } else {
            if (out.empty() || out.back() != l1[i]) {
                out.push_back(l1[i]);
            }
            int val = l1[i];
            while (i < l1.size() && l1[i] == val) ++i;
            while (j < l2.size() && l2[j] == val) ++j;
        }
    }

    return out;
}
