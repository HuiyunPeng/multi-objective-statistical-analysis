#include <vector>
using namespace std;

vector<int> tri(int n) {
    if (n == 0) return {1};
    if (n < 0) return {1, 3};

    vector<int> out(n + 1);
    out[0] = 1;
    out[1] = 3;

    for (int k = 1, i = 2; i <= n; ++k, i += 2) {
        out[i] = k + 1;
        if (i + 1 <= n) {
            out[i + 1] = static_cast<int>(1LL * (k + 1) * (k + 3));
        }
    }

    return out;
}
