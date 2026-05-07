#include <string>
using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    const char* p = brackets.data();
    const char* end = p + brackets.size();

    while (p != end) {
        const char c = *p++;
        if (c == '<') {
            ++level;
        } else if (c == '>') {
            if (level == 0) return false;
            --level;
        }
    }

    return level == 0;
}
