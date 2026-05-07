#include <vector>
#include <string>

using namespace std;

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    if (prefix.empty()) {
        return strings;
    }

    const size_t prefix_len = prefix.size();
    size_t match_count = 0;

    for (const string& s : strings) {
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            ++match_count;
        }
    }

    vector<string> out;
    out.reserve(match_count);

    for (string& s : strings) {
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            out.push_back(std::move(s));
        }
    }

    return out;
}
