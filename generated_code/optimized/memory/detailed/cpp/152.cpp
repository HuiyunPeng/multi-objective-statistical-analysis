#include <vector>
#include <cstdlib>
using namespace std;

vector<int> compare(vector<int> game, vector<int> guess) {
    const size_t n = game.size();
    for (size_t i = 0; i < n; ++i) {
        game[i] = abs(game[i] - guess[i]);
    }
    return game;
}
