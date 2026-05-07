#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int> lst) {
    sort(lst.begin(), lst.end());

    int ans = -1;
    const int n = static_cast<int>(lst.size());

    for (int i = 0; i < n; ) {
        int value = lst[i];
        int j = i + 1;
        while (j < n && lst[j] == value) ++j;

        int count = j - i;
        if ((value == 0 && count >= 2) || (value > 0 && count >= value)) {
            if (value > ans) ans = value;
        }

        i = j;
    }

    return ans;
}
