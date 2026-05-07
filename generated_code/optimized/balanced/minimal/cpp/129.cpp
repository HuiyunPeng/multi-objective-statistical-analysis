#include <vector>
using namespace std;

vector<int> minPath(vector<vector<int>> grid, int k) {
    if (k <= 0) return {};

    const int rows = static_cast<int>(grid.size());
    int x = -1, y = -1;

    for (int i = rows - 1; i >= 0; --i) {
        const int cols = static_cast<int>(grid[i].size());
        for (int j = cols - 1; j >= 0; --j) {
            if (grid[i][j] == 1) {
                x = i;
                y = j;
                goto found_one;
            }
        }
    }

found_one:
    int minVal = rows * rows;

    if (x != -1) {
        if (x > 0 && y < static_cast<int>(grid[x - 1].size()) && grid[x - 1][y] < minVal)
            minVal = grid[x - 1][y];
        if (x + 1 < rows && y < static_cast<int>(grid[x + 1].size()) && grid[x + 1][y] < minVal)
            minVal = grid[x + 1][y];
        if (y > 0 && grid[x][y - 1] < minVal)
            minVal = grid[x][y - 1];
        if (y + 1 < static_cast<int>(grid[x].size()) && grid[x][y + 1] < minVal)
            minVal = grid[x][y + 1];
    }

    vector<int> out(k);
    for (int i = 0; i < k; i += 2) {
        out[i] = 1;
        if (i + 1 < k) out[i + 1] = minVal;
    }
    return out;
}
