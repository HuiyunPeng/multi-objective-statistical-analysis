#include <vector>

using namespace std;

int max_fill(vector<vector<int>> grid, int capacity) {
    int out = 0;

    for (const auto& row : grid) {
        long long sum = 0;
        const int* p = row.data();
        const int* end = p + row.size();

        while (p != end) {
            sum += *p++;
        }

        if (sum > 0) {
            out += static_cast<int>((sum + capacity - 1) / capacity);
        }
    }

    return out;
}
