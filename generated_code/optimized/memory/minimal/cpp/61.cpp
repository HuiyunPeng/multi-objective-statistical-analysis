#include <string>
using namespace std;

bool correct_bracketing(string brackets) {
    int level = 0;
    for (char c : brackets) {
        if (c == '(') {
            ++level;
        } else if (c == ')') {
            if (--level < 0) return false;
        }
    }
    return level == 0;
}
