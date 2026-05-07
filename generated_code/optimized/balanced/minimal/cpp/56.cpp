#include <string>

using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    const char* s = brackets.c_str();

    for (size_t i = 0, n = brackets.size(); i < n; ++i) {
        if (s[i] == '<') {
            ++level;
        } else if (s[i] == '>') {
            if (level == 0) return false;
            --level;
        }
    }

    return level == 0;
}
