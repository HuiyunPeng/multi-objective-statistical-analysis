#include <vector>
#include <limits>
using namespace std;

vector<int> minPath(vector<vector<int>> grid, int k) {
    if (k <= 0) return {};

    const size_t rows = grid.size();
    int x = -1, y = -1;

    for (size_t i = 0; i < rows; ++i) {
        const auto& row = grid[i];
        for (size_t j = 0, cols = row.size(); j < cols; ++j) {
            if (row[j] == 1) {
                x = static_cast<int>(i);
                y = static_cast<int>(j);
            }
        }
    }

    if (x < 0) return {};

    int mn = numeric_limits<int>::max();

    if (x > 0 && static_cast<size_t>(y) < grid[x - 1].size()) {
        const int v = grid[x - 1][y];
        if (v < mn) mn = v;
    }
    if (static_cast<size_t>(x + 1) < rows && static_cast<size_t>(y) < grid[x + 1].size()) {
        const int v = grid[x + 1][y];
        if (v < mn) mn = v;
    }
    if (y > 0) {
        const int v = grid[x][y - 1];
        if (v < mn) mn = v;
    }
    if (static_cast<size_t>(y + 1) < grid[x].size()) {
        const int v = grid[x][y + 1];
        if (v < mn) mn = v;
    }

    if (mn == numeric_limits<int>::max()) {
        mn = static_cast<int>(rows * rows);
    }

    vector<int> out(k);
    for (int i = 0; i < k; i += 2) {
        out[i] = 1;
        if (i + 1 < k) out[i + 1] = mn;
    }

    return out;
}
