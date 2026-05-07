#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const int n = (int)lst.size();
    if (n < 2) return true;

    int prev2 = lst[0];
    int prev1 = lst[1];
    if (prev1 < prev2) return false;

    for (int i = 2; i < n; ++i) {
        const int cur = lst[i];
        if (cur < prev1) return false;
        if (cur == prev1 && cur == prev2) return false;
        prev2 = prev1;
        prev1 = cur;
    }

    return true;
}
