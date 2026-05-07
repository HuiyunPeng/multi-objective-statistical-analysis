#include <vector>
#include <cstdlib>
using namespace std;

vector<int> compare(vector<int> game, vector<int> guess) {
    for (size_t i = 0, n = game.size(); i < n; ++i) {
        game[i] = abs(game[i] - guess[i]);
    }
    return game;
}
