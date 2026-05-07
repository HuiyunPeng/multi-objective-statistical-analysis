#include <vector>
using namespace std;

vector<int> tri(int n) {
    if (n == 0) {
        return vector<int>(1, 1);
    }

    vector<int> out;

    if (n < 0) {
        out.resize(2);
        out[0] = 1;
        out[1] = 3;
        return out;
    }

    out.resize(n + 1);
    out[0] = 1;
    out[1] = 3;

    for (int i = 2; i <= n; ++i) {
        if ((i & 1) == 0) {
            out[i] = 1 + (i >> 1);
        } else {
            out[i] = out[i - 1] + out[i - 2] + 1 + ((i + 1) >> 1);
        }
    }

    return out;
}
