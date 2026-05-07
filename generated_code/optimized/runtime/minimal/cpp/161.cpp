#include <string>
#include <algorithm>
using namespace std;

string solve(string s) {
    bool allNonLetters = true;
    for (char &c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            c ^= 32;
            allNonLetters = false;
        }
    }
    if (allNonLetters) {
        reverse(s.begin(), s.end());
    }
    return s;
}
