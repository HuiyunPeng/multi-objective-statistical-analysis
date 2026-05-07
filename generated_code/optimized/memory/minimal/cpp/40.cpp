#include <vector>
#include <algorithm>

using namespace std;

bool triples_sum_to_zero(vector<int> l) {
    const int n = static_cast<int>(l.size());
    if (n < 3) return false;

    sort(l.begin(), l.end());

    for (int i = 0; i < n - 2; ++i) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            long long sum = static_cast<long long>(l[i]) + l[left] + l[right];
            if (sum == 0) return true;
            if (sum < 0) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return false;
}
