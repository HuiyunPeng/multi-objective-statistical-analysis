#include <string>
using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    const char* s = brackets.data();
    const size_t n = brackets.size();

    for (size_t i = 0; i < n; ++i) {
        level += (s[i] == '(') - (s[i] == ')');
        if (level < 0) return false;
    }

    return level == 0;
}
