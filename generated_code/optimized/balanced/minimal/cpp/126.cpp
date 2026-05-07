#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const size_t n = lst.size();
    if (n < 2) return true;

    const int* a = lst.data();
    int prev2 = a[0];
    int prev1 = a[1];

    if (prev1 < prev2) return false;

    for (size_t i = 2; i < n; ++i) {
        const int cur = a[i];
        if (cur < prev1 || (cur == prev1 && prev1 == prev2)) return false;
        prev2 = prev1;
        prev1 = cur;
    }

    return true;
}
