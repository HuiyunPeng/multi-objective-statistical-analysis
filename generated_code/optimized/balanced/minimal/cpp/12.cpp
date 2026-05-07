#include <string>
#include <vector>
using namespace std;

string longest(vector<string> strings) {
    if (strings.empty()) return {};

    size_t max_idx = 0;
    size_t max_len = strings[0].size();

    for (size_t i = 1, n = strings.size(); i < n; ++i) {
        const size_t len = strings[i].size();
        if (len > max_len) {
            max_len = len;
            max_idx = i;
        }
    }

    return std::move(strings[max_idx]);
}
