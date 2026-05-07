#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> sorted_list_sum(vector<string> lst) {
    vector<string> out;
    out.reserve(lst.size());

    for (const string& s : lst) {
        if ((s.size() & 1) == 0) out.push_back(s);
    }

    sort(out.begin(), out.end(), [](const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    return out;
}
