#include <vector>
#include <string>
#include <utility>

using namespace std;

string longest(vector<string> strings) {
    const size_t n = strings.size();
    if (n == 0) return string();

    size_t best = 0;
    size_t max_len = strings[0].size();

    for (size_t i = 1; i < n; ++i) {
        const size_t len = strings[i].size();
        if (len > max_len) {
            max_len = len;
            best = i;
        }
    }

    return std::move(strings[best]);
}
