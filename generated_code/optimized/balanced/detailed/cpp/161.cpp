#include <string>
#include <algorithm>

using namespace std;

string solve(string s) {
    const size_t n = s.size();
    size_t nonletters = 0;

    for (size_t i = 0; i < n; ++i) {
        char &c = s[i];
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c + ('a' - 'A'));
        } else if (c >= 'a' && c <= 'z') {
            c = static_cast<char>(c - ('a' - 'A'));
        } else {
            ++nonletters;
        }
    }

    if (nonletters == n) {
        reverse(s.begin(), s.end());
    }

    return s;
}
