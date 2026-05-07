#include <vector>
using std::vector;

vector<int> tri(int n) {
    if (n == 0) return {1};
    if (n < 0) return {1, 3};

    vector<int> out(n + 1);
    out[0] = 1;

    for (int k = 1, i = 1; i <= n; ++k) {
        out[i] = k * (k + 2);   // i = 2*k - 1
        if (++i > n) break;
        out[i] = k + 1;         // i = 2*k
        ++i;
    }

    return out;
}
