#include <string>
#include <algorithm>
using namespace std;

string solve(string s) {
    bool hasLetter = false;
    const size_t len = s.size();

    for (size_t i = 0; i < len; ++i) {
        char &w = s[i];
        if (w >= 'A' && w <= 'Z') {
            w = static_cast<char>(w + ('a' - 'A'));
            hasLetter = true;
        } else if (w >= 'a' && w <= 'z') {
            w = static_cast<char>(w - ('a' - 'A'));
            hasLetter = true;
        }
    }

    if (!hasLetter) {
        reverse(s.begin(), s.end());
    }

    return s;
}
