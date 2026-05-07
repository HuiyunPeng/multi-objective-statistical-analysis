#include <vector>
using namespace std;

int max_fill(vector<vector<int>> grid, int capacity) {
    int out = 0;
    const size_t rows = grid.size();

    for (size_t i = 0; i < rows; ++i) {
        const vector<int>& row = grid[i];
        const int* p = row.data();
        const int* end = p + row.size();

        int sum = 0;
        while (p != end) {
            sum += *p++;
        }

        if (sum > 0) {
            out += (sum + capacity - 1) / capacity;
        }
    }

    return out;
}
