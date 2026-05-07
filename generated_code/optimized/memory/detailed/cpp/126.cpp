#include <vector>
using namespace std;

bool is_sorted(vector<int> lst) {
    const int n = static_cast<int>(lst.size());
    for (int i = 1; i < n; ++i) {
        if (lst[i] < lst[i - 1]) return false;
        if (i > 1 && lst[i] == lst[i - 1] && lst[i] == lst[i - 2]) return false;
    }
    return true;
}
