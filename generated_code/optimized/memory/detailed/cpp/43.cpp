#include <vector>
#include <algorithm>
using namespace std;

bool pairs_sum_to_zero(vector<int> l) {
    if (l.size() < 2) return false;

    sort(l.begin(), l.end());

    size_t i = 0;
    size_t j = l.size() - 1;

    while (i < j) {
        long long sum = static_cast<long long>(l[i]) + l[j];
        if (sum == 0) return true;
        if (sum < 0) {
            ++i;
        } else {
            --j;
        }
    }

    return false;
}
