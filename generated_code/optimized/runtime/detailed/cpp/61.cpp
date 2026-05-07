#include <string>

using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    const char* s = brackets.data();
    const size_t n = brackets.size();

    for (size_t i = 0; i < n; ++i) {
        const char c = s[i];
        level += (c == '(');
        level -= (c == ')');

        if (level < 0) return false;
        if (level > static_cast<int>(n - i - 1)) return false;
    }

    return level == 0;
}
