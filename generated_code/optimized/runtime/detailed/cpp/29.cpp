#include <vector>
#include <string>
using namespace std;

vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    vector<string> out;
    out.reserve(strings.size());

    const size_t prefix_len = prefix.size();
    const size_t n = strings.size();

    for (size_t i = 0; i < n; ++i) {
        const string& s = strings[i];
        if (s.size() >= prefix_len && s.compare(0, prefix_len, prefix) == 0) {
            out.push_back(s);
        }
    }

    return out;
}
