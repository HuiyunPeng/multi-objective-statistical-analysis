#include <vector>
#include <cstdlib>

using namespace std;

vector<int> compare(vector<int> game, vector<int> guess) {
    const size_t n = game.size();
    vector<int> out(n);
    for (size_t i = 0; i < n; ++i) {
        out[i] = abs(game[i] - guess[i]);
    }
    return out;
}
