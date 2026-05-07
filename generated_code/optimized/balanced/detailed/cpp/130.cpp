#include <vector>
using namespace std;

vector<int> tri(int n) {
    if (n < 0) return {1, 3};

    vector<int> out(n + 1);
    for (int k = 0, i = 0; i <= n; ++k, i += 2) {
        out[i] = k + 1;
        if (i + 1 <= n) {
            out[i + 1] = static_cast<int>(1LL * (k + 1) * (k + 3));
        }
    }
    return out;
}
