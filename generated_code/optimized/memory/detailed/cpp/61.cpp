#include <string>

using std::string;

bool correct_bracketing(string brackets) {
    int level = 0;
    for (char c : brackets) {
        if (c == '(') {
            ++level;
        } else if (c == ')') {
            if (level == 0) return false;
            --level;
        }
    }
    return level == 0;
}
