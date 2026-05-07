#include <vector>
using namespace std;

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    vector<vector<int>> out;
    const size_t rows = lst.size();

    for (size_t i = 0; i < rows; ++i) {
        const auto& row = lst[i];
        for (size_t j = row.size(); j-- > 0;) {
            if (row[j] == x) {
                out.push_back({static_cast<int>(i), static_cast<int>(j)});
            }
        }
    }

    return out;
}
