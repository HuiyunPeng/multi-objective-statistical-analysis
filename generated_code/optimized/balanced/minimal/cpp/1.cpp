#include <string>
#include <vector>
using namespace std;

vector<string> separate_paren_groups(string paren_string) {
    vector<string> all_parens;
    const size_t n = paren_string.size();
    all_parens.reserve(n / 2);

    int level = 0;
    size_t start = 0;
    const char* data = paren_string.data();

    for (size_t i = 0; i < n; ++i) {
        const char c = data[i];
        if (c == '(') {
            if (level++ == 0) start = i;
        } else if (c == ')') {
            if (--level == 0) {
                all_parens.emplace_back(data + start, i - start + 1);
            }
        }
    }

    return all_parens;
}
