#include <vector>
using namespace std;

vector<int> tri(int n) {
    if (n == 0) return {1};

    vector<int> out(n + 1);
    out[0] = 1;
    out[1] = 3;

    for (int i = 2; i <= n; i += 2) {
        const int half = i >> 1;
        out[i] = half + 1;
        if (i + 1 <= n) {
            out[i + 1] = out[i] + out[i - 1] + half + 2;
        }
    }

    return out;
}
