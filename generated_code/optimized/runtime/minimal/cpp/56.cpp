#include <string>

bool correct_bracketing(std::string brackets) {
    int level = 0;
    const char* s = brackets.data();
    const size_t n = brackets.size();

    for (size_t i = 0; i < n; ++i) {
        const char c = s[i];
        if (c == '<') {
            ++level;
        } else if (c == '>') {
            if (--level < 0) return false;
        }
    }

    return level == 0;
}
