#include <vector>
using namespace std;

vector<int> minPath(vector<vector<int>> grid, int k) {
    const int rows = static_cast<int>(grid.size());
    int x = -1, y = -1;

    for (int i = 0; i < rows && x == -1; ++i) {
        const int cols = static_cast<int>(grid[i].size());
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                x = i;
                y = j;
                break;
            }
        }
    }

    int mn = rows * rows;
    if (x > 0 && y < static_cast<int>(grid[x - 1].size()) && grid[x - 1][y] < mn) mn = grid[x - 1][y];
    if (x + 1 < rows && y < static_cast<int>(grid[x + 1].size()) && grid[x + 1][y] < mn) mn = grid[x + 1][y];
    if (y > 0 && grid[x][y - 1] < mn) mn = grid[x][y - 1];
    if (y + 1 < static_cast<int>(grid[x].size()) && grid[x][y + 1] < mn) mn = grid[x][y + 1];

    vector<int> out(k, 1);
    for (int i = 1; i < k; i += 2) {
        out[i] = mn;
    }

    return out;
}
