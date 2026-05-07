#include <vector>
using namespace std;

vector<int> compare(vector<int> game, vector<int> guess) {
    const size_t n = game.size();
    vector<int> out(n);

    const int* g = game.data();
    const int* h = guess.data();
    int* o = out.data();

    for (size_t i = 0; i < n; ++i) {
        const int diff = g[i] - h[i];
        o[i] = diff < 0 ? -diff : diff;
    }

    return out;
}
