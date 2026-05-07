#include <vector>
#include <string>
using namespace std;

vector<string> separate_paren_groups(string paren_string) {
    vector<string> all_parens;
    int level = 0, start = -1;

    for (size_t i = 0; i < paren_string.size(); ++i) {
        char chr = paren_string[i];
        if (chr == '(') {
            if (level == 0) start = static_cast<int>(i);
            ++level;
        } else if (chr == ')') {
            --level;
            if (level == 0 && start != -1) {
                all_parens.emplace_back(paren_string, start, i - start + 1);
            }
        }
    }

    return all_parens;
}
