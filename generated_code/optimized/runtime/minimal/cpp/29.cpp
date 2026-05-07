#include <vector>
#include <string>
using namespace std;

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    if (prefix.empty()) return strings;

    vector<string> out;
    out.reserve(strings.size());

    const size_t prefix_len = prefix.size();
    for (size_t i = 0, n = strings.size(); i < n; ++i) {
        if (strings[i].compare(0, prefix_len, prefix) == 0) {
            out.emplace_back(std::move(strings[i]));
        }
    }

    return out;
}
