#include <vector>

using namespace std;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }

    int end = (b < 10) ? b : 9;
    if (a > end) return {};

    int start = (a % 2 == 0) ? a : a + 1;
    int last = (end % 2 == 0) ? end : end - 1;
    if (start > last) return {};

    int count = ((last - start) >> 1) + 1;
    vector<int> out(count);
    for (int i = 0, v = start; i < count; ++i, v += 2) {
        out[i] = v;
    }
    return out;
}
