#include <vector>
#include <algorithm>
using namespace std;

bool triples_sum_to_zero(vector<int> l) {
    const int n = static_cast<int>(l.size());
    if (n < 3) return false;

    sort(l.begin(), l.end());

    if (l[0] > 0 || l[n - 1] < 0) return false;

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && l[i] == l[i - 1]) continue;

        if ((long long)l[i] + l[i + 1] + l[i + 2] > 0) break;
        if ((long long)l[i] + l[n - 2] + l[n - 1] < 0) continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            long long sum = (long long)l[i] + l[left] + l[right];
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
