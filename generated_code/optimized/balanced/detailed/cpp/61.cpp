#include <string>

using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    const size_t n = brackets.size();

    if (n & 1) return false;

    for (size_t i = 0; i < n; ++i) {
        const char c = brackets[i];
        if (c == '(') {
            ++level;
        } else if (c == ')') {
            if (level == 0) return false;
            --level;
        }
    }

    return level == 0;
}
