#include <vector>
#include <algorithm>

using namespace std;

int search(vector<int> lst) {
    if (lst.empty()) return -1;

    sort(lst.begin(), lst.end());

    int best = -1;
    const int n = static_cast<int>(lst.size());

    for (int i = 0; i < n; ) {
        const int value = lst[i];
        int j = i + 1;
        while (j < n && lst[j] == value) ++j;

        const int count = j - i;

        if (value == 1) {
            if (best < 1) best = 1;
        } else if (value > 1) {
            if (count >= value && value > best) best = value;
        } else if (value == 0) {
            if (count >= 2 && best < 0) best = 0;
        }

        i = j;
    }

    return best;
}
