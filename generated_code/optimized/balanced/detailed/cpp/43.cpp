#include <vector>
#include <algorithm>

using namespace std;

bool pairs_sum_to_zero(vector<int> l) {
    if (l.size() < 2) return false;

    sort(l.begin(), l.end());

    size_t left = 0;
    size_t right = l.size() - 1;

    while (left < right) {
        const int sum = l[left] + l[right];
        if (sum == 0) return true;
        if (sum < 0) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}
