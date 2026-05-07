#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
#include <algorithm>
#include <math.h>
#include <stdlib.h>

vector<string> separate_paren_groups(string paren_string) {
    vector<string> all_parens;
    const size_t n = paren_string.size();
    int level = 0;
    size_t start = 0;

    for (size_t i = 0; i < n; ++i) {
        const char chr = paren_string[i];
        if (chr == '(') {
            if (level == 0) start = i;
            ++level;
        } else if (chr == ')') {
            --level;
            if (level == 0) {
                all_parens.emplace_back(paren_string, start, i - start + 1);
            }
        }
    }

    return all_parens;
}
