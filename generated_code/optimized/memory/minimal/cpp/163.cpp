#include <vector>
using namespace std;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }

    if (a > 9) return {};

    int end = (b < 9) ? b : 9;
    if (a > end) return {};

    int first = (a % 2 == 0) ? a : a + 1;
    if (first > end) return {};

    int last = (end % 2 == 0) ? end : end - 1;

    vector<int> out;
    out.reserve((last - first) / 2 + 1);
    for (int i = first; i <= last; i += 2) {
        out.push_back(i);
    }
    return out;
}
