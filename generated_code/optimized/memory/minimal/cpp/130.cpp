#include <vector>
using namespace std;

vector<int> tri(int n) {
    if (n == 0) return {1};
    if (n < 0) return {1, 3};

    vector<int> out(n + 1);
    out[0] = 1;
    out[1] = 3;

    for (int i = 2; i <= n; ++i) {
        if ((i & 1) == 0) {
            out[i] = 1 + i / 2;
        } else {
            out[i] = out[i - 1] + out[i - 2] + 1 + (i + 1) / 2;
        }
    }

    return out;
}
