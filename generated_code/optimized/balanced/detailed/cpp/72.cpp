#include <vector>
using namespace std;

bool will_it_fly(vector<int> q, int w) {
    const int n = static_cast<int>(q.size());
    long long sum = 0;

    int i = 0, j = n - 1;
    while (i < j) {
        const int left = q[i];
        const int right = q[j];
        if (left != right) return false;
        sum += static_cast<long long>(left) + right;
        ++i;
        --j;
    }

    if (i == j) {
        sum += q[i];
    }

    return sum <= w;
}
