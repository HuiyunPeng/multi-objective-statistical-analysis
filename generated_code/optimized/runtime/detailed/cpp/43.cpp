#include <vector>
#include <algorithm>
using namespace std;

bool pairs_sum_to_zero(vector<int> l) {
    if (l.size() < 2) return false;

    sort(l.begin(), l.end());

    int left = 0;
    int right = static_cast<int>(l.size()) - 1;

    while (left < right) {
        long long sum = static_cast<long long>(l[left]) + l[right];
        if (sum == 0) return true;
        if (sum < 0)
            ++left;
        else
            --right;
    }

    return false;
}
