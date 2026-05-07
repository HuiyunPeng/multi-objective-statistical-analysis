#include <vector>
#include <string>
using namespace std;

vector<string> separate_paren_groups(string paren_string) {
    vector<string> all_parens;
    const size_t n = paren_string.size();
    all_parens.reserve(n >> 1);

    int level = 0;
    size_t start = 0;

    for (size_t i = 0; i < n; ++i) {
        const char c = paren_string[i];
        if (c == '(') {
            if (level == 0) start = i;
            ++level;
        } else if (c == ')') {
            --level;
            if (level == 0) {
                all_parens.emplace_back(paren_string.substr(start, i - start + 1));
            }
        }
    }

    return all_parens;
}
