#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> sorted_list_sum(vector<string> lst) {
    size_t write = 0;
    const size_t n = lst.size();

    for (size_t i = 0; i < n; ++i) {
        if ((lst[i].size() & 1u) == 0) {
            if (write != i) lst[write] = std::move(lst[i]);
            ++write;
        }
    }

    lst.resize(write);

    sort(lst.begin(), lst.end(), [](const string& a, const string& b) {
        const size_t la = a.size();
        const size_t lb = b.size();
        return la == lb ? a < b : la < lb;
    });

    return lst;
}
