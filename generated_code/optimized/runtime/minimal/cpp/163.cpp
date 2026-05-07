#include <vector>
using namespace std;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }

    const int upper = (b < 9) ? b : 9;
    if (a > upper) return {};

    int start = (a & 1) ? (a + 1) : a;
    if (start > upper) return {};

    vector<int> out;
    out.reserve(static_cast<size_t>((upper - start) / 2 + 1));
    for (int i = start; i <= upper; i += 2) {
        out.push_back(i);
    }
    return out;
}
