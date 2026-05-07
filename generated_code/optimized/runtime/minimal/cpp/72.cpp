#include <vector>
using namespace std;

bool will_it_fly(vector<int> q, int w) {
    long long sum = 0;
    size_t i = 0, j = q.size();

    while (i < j) {
        --j;
        if (q[i] != q[j]) return false;

        if (i == j) {
            sum += q[i];
        } else {
            sum += static_cast<long long>(q[i]) + q[j];
        }
        ++i;
    }

    return sum <= w;
}
