#include <vector>
using std::vector;

bool will_it_fly(vector<int> q, int w) {
    const size_t n = q.size();
    long long sum = 0;

    for (size_t i = 0; i < n / 2; ++i) {
        if (q[i] != q[n - 1 - i]) return false;
        sum += static_cast<long long>(q[i]) + q[n - 1 - i];
    }

    if (n & 1) sum += q[n / 2];

    return sum <= w;
}
