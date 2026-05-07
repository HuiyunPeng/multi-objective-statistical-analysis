#include <vector>
using namespace std;

vector<int> make_a_pile(int n) {
    vector<int> out;
    if (n > 0) out.reserve(n);
    out.push_back(n);

    int value = n;
    for (int i = 1; i < n; ++i) {
        value += 2;
        out.push_back(value);
    }

    return out;
}
