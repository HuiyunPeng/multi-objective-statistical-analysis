#include <vector>
#include <string>
using namespace std;

vector<int> parse_nested_parens(string paren_string) {
    vector<int> all_levels;
    all_levels.reserve(paren_string.size() >> 1);

    int level = 0;
    int max_level = 0;

    const char* s = paren_string.data();
    const size_t n = paren_string.size();

    for (size_t i = 0; i < n; ++i) {
        const char chr = s[i];
        if (chr == '(') {
            ++level;
            if (level > max_level) max_level = level;
        } else if (chr == ')') {
            --level;
            if (level == 0) {
                all_levels.push_back(max_level);
                max_level = 0;
            }
        }
    }

    return all_levels;
}
