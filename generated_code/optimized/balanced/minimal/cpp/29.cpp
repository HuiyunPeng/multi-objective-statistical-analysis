#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    if (prefix.empty()) return strings;

    const size_t prefix_len = prefix.size();
    vector<string> out;
    out.reserve(strings.size());

    for (string& s : strings) {
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            out.push_back(std::move(s));
        }
    }

    out.shrink_to_fit();
    return out;
}
