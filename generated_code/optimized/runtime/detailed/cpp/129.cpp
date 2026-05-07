#include <vector>
using namespace std;

vector<int> minPath(vector<vector<int>> grid, int k) {
    if (k <= 0) return {};

    const int rows = static_cast<int>(grid.size());
    int x = -1, y = -1;

    for (int i = 0; i < rows; ++i) {
        const vector<int>& row = grid[i];
        const int cols = static_cast<int>(row.size());
        for (int j = 0; j < cols; ++j) {
            if (row[j] == 1) {
                x = i;
                y = j;
            }
        }
    }

    int minVal = rows * rows;
    if (x >= 0) {
        if (x > 0) {
            const int v = grid[x - 1][y];
            if (v < minVal) minVal = v;
        }
        if (x + 1 < rows) {
            const int v = grid[x + 1][y];
            if (v < minVal) minVal = v;
        }
        if (y > 0) {
            const int v = grid[x][y - 1];
            if (v < minVal) minVal = v;
        }
        const int cols = static_cast<int>(grid[x].size());
        if (y + 1 < cols) {
            const int v = grid[x][y + 1];
            if (v < minVal) minVal = v;
        }
    }

    vector<int> out(k);
    int i = 0;
    for (; i + 1 < k; i += 2) {
        out[i] = 1;
        out[i + 1] = minVal;
    }
    if (i < k) out[i] = 1;

    return out;
}
