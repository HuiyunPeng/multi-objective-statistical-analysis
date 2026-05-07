#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

vector<string> sorted_list_sum(vector<string> lst) {
    size_t write = 0;
    for (size_t read = 0; read < lst.size(); ++read) {
        if ((lst[read].size() & 1u) == 0) {
            if (write != read) lst[write] = move(lst[read]);
            ++write;
        }
    }

    lst.resize(write);

    sort(lst.begin(), lst.end(), [](const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    return lst;
}
