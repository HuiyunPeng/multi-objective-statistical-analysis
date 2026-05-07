#include <string>
using namespace std;

string encrypt(string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = (char)(((int)s[i] + 4 - (int)'a') % 26 + (int)'a');
    }
    return s;
}
