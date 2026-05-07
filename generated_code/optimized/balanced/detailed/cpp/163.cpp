#include <vector>
using std::vector;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int t = a;
        a = b;
        b = t;
    }

    if (a >= 10) return {};

    const int upper = (b < 10) ? b : 8;
    int start = (a % 2 == 0) ? a : (a + 1);

    if (start > upper) return {};

    const size_t count =
        static_cast<size_t>((static_cast<long long>(upper) - static_cast<long long>(start)) / 2 + 1);

    vector<int> out(count);
    for (size_t i = 0; i < count; ++i) {
        out[i] = start + static_cast<int>(i * 2);
    }

    return out;
}
