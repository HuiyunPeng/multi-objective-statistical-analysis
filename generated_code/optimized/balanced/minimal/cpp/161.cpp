#include <string>
#include <algorithm>
using namespace std;

string solve(string s) {
    size_t nonletters = 0;

    for (char& c : s) {
        unsigned char uc = static_cast<unsigned char>(c);
        unsigned char lower = static_cast<unsigned char>(uc | 32);

        if (lower >= 'a' && lower <= 'z') {
            c = static_cast<char>(uc ^ 32);
        } else {
            ++nonletters;
        }
    }

    if (nonletters == s.size()) {
        reverse(s.begin(), s.end());
    }

    return s;
}
