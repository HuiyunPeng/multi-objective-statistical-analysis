#include <vector>
using namespace std;

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    vector<vector<int>> out;
    const int rows = static_cast<int>(lst.size());

    for (int i = 0; i < rows; ++i) {
        const vector<int>& row = lst[i];
        for (int j = static_cast<int>(row.size()) - 1; j >= 0; --j) {
            if (row[j] == x) {
                out.push_back({i, j});
            }
        }
    }

    return out;
}
