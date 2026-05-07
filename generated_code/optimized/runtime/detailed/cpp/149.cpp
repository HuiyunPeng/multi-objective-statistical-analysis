#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> sorted_list_sum(vector<string> lst) {
    vector<string> out;
    out.reserve(lst.size());

    for (const string& s : lst) {
        if ((s.size() & 1u) == 0) {
            out.push_back(s);
        }
    }

    sort(out.begin(), out.end(), [](const string& a, const string& b) {
        const size_t la = a.size();
        const size_t lb = b.size();
        return (la < lb) || (la == lb && a < b);
    });

    return out;
}
