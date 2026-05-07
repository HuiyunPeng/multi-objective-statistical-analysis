#include <vector>
using namespace std;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }

    if (a >= 10) return {};

    int end = (b < 8) ? b : 8;
    int start = (a % 2 == 0) ? a : a + 1;

    if (start > end) return {};

    vector<int> out;
    out.reserve((end - start) / 2 + 1);
    for (int i = start; i <= end; i += 2) {
        out.push_back(i);
    }
    return out;
}
