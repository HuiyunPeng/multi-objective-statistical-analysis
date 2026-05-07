#include <vector>
using namespace std;

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    size_t count = 0;
    for (const auto& row : lst) {
        for (size_t j = row.size(); j-- > 0;) {
            if (row[j] == x) ++count;
        }
    }

    vector<vector<int>> out;
    out.reserve(count);

    for (size_t i = 0; i < lst.size(); ++i) {
        const auto& row = lst[i];
        for (size_t j = row.size(); j-- > 0;) {
            if (row[j] == x) {
                out.emplace_back();
                out.back().reserve(2);
                out.back().push_back(static_cast<int>(i));
                out.back().push_back(static_cast<int>(j));
            }
        }
    }

    return out;
}
