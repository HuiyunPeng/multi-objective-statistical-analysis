#include <vector>
using namespace std;

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    vector<vector<int>> out;
    out.reserve(lst.size());

    const int n = static_cast<int>(lst.size());
    for (int i = 0; i < n; ++i) {
        const vector<int>& row = lst[i];
        for (int j = static_cast<int>(row.size()); j-- > 0;) {
            if (row[j] == x) {
                out.push_back(vector<int>{i, j});
            }
        }
    }

    return out;
}
