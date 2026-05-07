#include <vector>
#include <cstdlib>

using namespace std;

vector<int> compare(vector<int> game, vector<int> guess) {
    const size_t n = game.size();
    int* g = game.data();
    const int* q = guess.data();

    for (size_t i = 0; i < n; ++i) {
        g[i] = abs(g[i] - q[i]);
    }

    return game;
}
