#include <vector>
#include <string>
using namespace std;

vector<int> parse_nested_parens(string paren_string) {
    vector<int> all_levels;
    all_levels.reserve(paren_string.size() >> 1);

    int level = 0;
    int max_level = 0;

    for (char chr : paren_string) {
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
