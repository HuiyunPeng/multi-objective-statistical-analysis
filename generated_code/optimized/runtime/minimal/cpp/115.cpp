#include <vector>
using namespace std;

int max_fill(vector<vector<int>> grid, int capacity) {
    long long out = 0;
    for (const auto& row : grid) {
        long long sum = 0;
        for (int v : row) sum += v;
        if (sum > 0) out += (sum + capacity - 1) / capacity;
    }
    return static_cast<int>(out);
}
