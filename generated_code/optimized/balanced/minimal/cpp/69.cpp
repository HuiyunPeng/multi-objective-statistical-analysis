#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int> lst) {
    if (lst.empty()) return -1;

    sort(lst.begin(), lst.end());

    for (int i = static_cast<int>(lst.size()) - 1; i >= 0;) {
        int value = lst[i];
        int j = i - 1;
        while (j >= 0 && lst[j] == value) --j;
        int count = i - j;

        if (value > 1) {
            if (count >= value) return value;
        } else if (value == 1) {
            return 1;
        } else if (value == 0) {
            return (count >= 2) ? 0 : -1;
        } else {
            return -1;
        }

        i = j;
    }

    return -1;
}
