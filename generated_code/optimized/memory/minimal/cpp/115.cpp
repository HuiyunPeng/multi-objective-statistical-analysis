#include <vector>

int max_fill(std::vector<std::vector<int>> grid, int capacity) {
    int out = 0;
    for (const auto& row : grid) {
        int sum = 0;
        for (int value : row) {
            sum += value;
        }
        if (sum > 0) {
            out += (sum + capacity - 1) / capacity;
        }
    }
    return out;
}
