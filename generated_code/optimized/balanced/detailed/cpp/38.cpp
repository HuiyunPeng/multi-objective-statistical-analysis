#include <string>
using namespace std;

string encode_cyclic(string s) {
    const size_t l = s.size();
    for (size_t i = 0; i + 2 < l; i += 3) {
        const char t = s[i];
        s[i] = s[i + 1];
        s[i + 1] = s[i + 2];
        s[i + 2] = t;
    }
    return s;
}

string decode_cyclic(string s) {
    const size_t l = s.size();
    for (size_t i = 0; i + 2 < l; i += 3) {
        const char t = s[i + 2];
        s[i + 2] = s[i + 1];
        s[i + 1] = s[i];
        s[i] = t;
    }
    return s;
}
