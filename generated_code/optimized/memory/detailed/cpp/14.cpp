#include <vector>
#include <string>

using namespace std;

vector<string> all_prefixes(string str) {
    vector<string> out;
    out.reserve(str.size());
    for (size_t i = 0, n = str.size(); i < n; ++i) {
        out.emplace_back(str, 0, i + 1);
    }
    return out;
}
