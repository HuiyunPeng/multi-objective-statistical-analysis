#include <vector>

std::vector<int> minPath(std::vector<std::vector<int>> grid, int k) {
    int x = -1, y = -1;
    const int rows = static_cast<int>(grid.size());

    for (int i = 0; i < rows; ++i) {
        const int cols = static_cast<int>(grid[i].size());
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                x = i;
                y = j;
            }
        }
    }

    int minVal = rows * rows;
    if (x != -1) {
        if (x > 0 && y < static_cast<int>(grid[x - 1].size()) && grid[x - 1][y] < minVal) minVal = grid[x - 1][y];
        if (x + 1 < rows && y < static_cast<int>(grid[x + 1].size()) && grid[x + 1][y] < minVal) minVal = grid[x + 1][y];
        if (y > 0 && grid[x][y - 1] < minVal) minVal = grid[x][y - 1];
        if (y + 1 < static_cast<int>(grid[x].size()) && grid[x][y + 1] < minVal) minVal = grid[x][y + 1];
    }

    std::vector<int> out(k);
    for (int i = 0; i < k; ++i) {
        out[i] = (i % 2 == 0) ? 1 : minVal;
    }

    return out;
}
