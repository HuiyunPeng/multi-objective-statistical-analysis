#include <vector>
#include <algorithm>
using namespace std;

bool pairs_sum_to_zero(vector<int> l) {
    sort(l.begin(), l.end());

    int i = 0;
    int j = (int)l.size() - 1;

    while (i < j) {
        long long sum = (long long)l[i] + l[j];
        if (sum == 0) return true;
        if (sum < 0) {
            ++i;
        } else {
            --j;
        }
    }

    return false;
}
