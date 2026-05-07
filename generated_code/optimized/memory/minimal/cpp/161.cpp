#include <string>
#include <algorithm>
using namespace std;

string solve(string s) {
    int nletter = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char &w = s[i];
        if (w >= 'A' && w <= 'Z') {
            w = w + ('a' - 'A');
        } else if (w >= 'a' && w <= 'z') {
            w = w - ('a' - 'A');
        } else {
            ++nletter;
        }
    }
    if (nletter == static_cast<int>(s.size())) {
        reverse(s.begin(), s.end());
    }
    return s;
}
