#include <vector>
using namespace std;

vector<int> minPath(vector<vector<int>> grid, int k) {
    const int rows = (int)grid.size();
    int x = -1, y = -1;

    for (int i = rows - 1; i >= 0 && x == -1; --i) {
        for (int j = (int)grid[i].size() - 1; j >= 0; --j) {
            if (grid[i][j] == 1) {
                x = i;
                y = j;
                break;
            }
        }
    }

    int best = rows * rows;
    if (x != -1) {
        if (x > 0 && y < (int)grid[x - 1].size() && grid[x - 1][y] < best) best = grid[x - 1][y];
        if (x + 1 < rows && y < (int)grid[x + 1].size() && grid[x + 1][y] < best) best = grid[x + 1][y];
        if (y > 0 && grid[x][y - 1] < best) best = grid[x][y - 1];
        if (y + 1 < (int)grid[x].size() && grid[x][y + 1] < best) best = grid[x][y + 1];
    }

    vector<int> out;
    if (k <= 0) return out;

    out.resize(k);
    for (int i = 0; i < k; i += 2) out[i] = 1;
    for (int i = 1; i < k; i += 2) out[i] = best;

    return out;
}
