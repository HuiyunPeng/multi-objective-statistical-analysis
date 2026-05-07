#include <string>
using namespace std;

string encrypt(string s) {
    const size_t n = s.size();
    for (size_t i = 0; i < n; ++i) {
        s[i] = static_cast<char>(((int)s[i] + 4 - (int)'a') % 26 + (int)'a');
    }
    return s;
}
