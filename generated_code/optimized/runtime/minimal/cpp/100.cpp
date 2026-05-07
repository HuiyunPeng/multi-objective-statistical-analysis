#include <vector>
using namespace std;

vector<int> make_a_pile(int n) {
    vector<int> out(n);
    for (int i = 0, val = n; i < n; ++i, val += 2) {
        out[i] = val;
    }
    return out;
}
