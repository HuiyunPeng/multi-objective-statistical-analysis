#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const size_t n = lst.size();
    if (n < 2) return true;

    int prev2 = lst[0];
    int prev1 = lst[0];

    for (size_t i = 1; i < n; ++i) {
        const int curr = lst[i];
        if (curr < prev1) return false;
        if (i >= 2 && curr == prev1 && prev1 == prev2) return false;
        prev2 = prev1;
        prev1 = curr;
    }

    return true;
}
