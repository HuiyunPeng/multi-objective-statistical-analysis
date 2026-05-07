#include <vector>
using namespace std;

vector<int> make_a_pile(int n) {
    if (n <= 0) return {n};

    vector<int> out(n);
    int value = n;
    for (int i = 0; i < n; ++i, value += 2) {
        out[i] = value;
    }
    return out;
}
