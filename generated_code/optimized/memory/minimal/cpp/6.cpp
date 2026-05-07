#include <vector>
#include <string>
using namespace std;

vector<int> parse_nested_parens(string paren_string) {
    int groups = 0;
    int level = 0;
    for (char c : paren_string) {
        if (c == '(') {
            ++level;
        } else if (c == ')') {
            --level;
            if (level == 0) {
                ++groups;
            }
        }
    }

    vector<int> all_levels;
    all_levels.reserve(groups);

    level = 0;
    int max_level = 0;
    for (char c : paren_string) {
        if (c == '(') {
            ++level;
            if (level > max_level) {
                max_level = level;
            }
        } else if (c == ')') {
            --level;
            if (level == 0) {
                all_levels.push_back(max_level);
                max_level = 0;
            }
        }
    }

    return all_levels;
}
