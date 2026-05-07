#include <vector>
#include <string>
using namespace std;

vector<string> separate_paren_groups(string paren_string) {
    vector<string> all_parens;

    int level = 0;
    size_t groups = 0;
    const size_t n = paren_string.size();

    for (size_t i = 0; i < n; ++i) {
        if (paren_string[i] == '(') {
            if (level == 0) ++groups;
            ++level;
        } else if (paren_string[i] == ')') {
            --level;
        }
    }

    all_parens.reserve(groups);

    level = 0;
    size_t start = 0;
    for (size_t i = 0; i < n; ++i) {
        if (paren_string[i] == '(') {
            if (level == 0) start = i;
            ++level;
        } else if (paren_string[i] == ')') {
            --level;
            if (level == 0) {
                all_parens.emplace_back(paren_string, start, i - start + 1);
            }
        }
    }

    return all_parens;
}
