#include <vector>
using namespace std;

bool will_it_fly(vector<int> q, int w) {
    long long sum = 0;
    size_t i = 0, j = q.size();

    while (i < j) {
        if (q[i] != q[j - 1]) return false;
        sum += q[i];
        if (i != j - 1) sum += q[j - 1];
        ++i;
        --j;
    }

    return sum <= w;
}
