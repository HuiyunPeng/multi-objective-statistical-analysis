#include <vector>
using namespace std;

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    size_t count = 0;
    for (const auto& row : lst) {
        for (int j = static_cast<int>(row.size()); j-- > 0;) {
            if (row[j] == x) {
                ++count;
            }
        }
    }

    vector<vector<int>> out;
    out.reserve(count);

    for (int i = 0, n = static_cast<int>(lst.size()); i < n; ++i) {
        const auto& row = lst[i];
        for (int j = static_cast<int>(row.size()); j-- > 0;) {
            if (row[j] == x) {
                out.emplace_back(2);
                out.back()[0] = i;
                out.back()[1] = j;
            }
        }
    }

    return out;
}
