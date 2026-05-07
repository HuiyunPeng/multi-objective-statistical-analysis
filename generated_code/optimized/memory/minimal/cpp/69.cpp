#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int> lst) {
    sort(lst.begin(), lst.end());

    int mx = -1;
    const int n = static_cast<int>(lst.size());

    for (int i = 0; i < n; ) {
        int v = lst[i];
        int j = i + 1;
        while (j < n && lst[j] == v) ++j;
        int cnt = j - i;

        if (v > 1) {
            if (cnt >= v) mx = v;
        } else if (v == 1) {
            if (mx < 1 && (mx == -1 || cnt >= 2)) mx = 1;
        } else if (v == 0) {
            if (mx < 0 && cnt >= 2) mx = 0;
        }

        i = j;
    }

    return mx;
}
