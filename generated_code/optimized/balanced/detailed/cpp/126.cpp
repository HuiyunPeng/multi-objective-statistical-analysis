#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const size_t n = lst.size();
    if (n < 2) return true;

    int prev = lst[0];
    int equal_count = 1;

    for (size_t i = 1; i < n; ++i) {
        const int cur = lst[i];

        if (cur < prev) return false;

        if (cur == prev) {
            if (++equal_count >= 3) return false;
        } else {
            equal_count = 1;
            prev = cur;
        }
    }

    return true;
}
