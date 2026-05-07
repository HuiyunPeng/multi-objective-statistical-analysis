#include <vector>
using namespace std;

vector<int> make_a_pile(int n) {
    vector<int> out(n);
    for (int i = 0; i < n; ++i)
        out[i] = n + 2 * i;
    return out;
}
