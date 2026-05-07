#include <string>
#include <algorithm>
using namespace std;

string solve(string s) {
    size_t nonLetter = 0;
    const size_t n = s.size();

    for (size_t i = 0; i < n; ++i) {
        char &w = s[i];
        if (w >= 'A' && w <= 'Z') w += 32;
        else if (w >= 'a' && w <= 'z') w -= 32;
        else ++nonLetter;
    }

    if (nonLetter == n) {
        reverse(s.begin(), s.end());
    }

    return s;
}
