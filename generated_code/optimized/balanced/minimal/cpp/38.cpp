#include <string>
using std::string;

string encode_cyclic(string s){
    const int l = static_cast<int>(s.size());
    for (int i = 0; i + 2 < l; i += 3) {
        const char t = s[i];
        s[i] = s[i + 1];
        s[i + 1] = s[i + 2];
        s[i + 2] = t;
    }
    return s;
}

string decode_cyclic(string s){
    const int l = static_cast<int>(s.size());
    for (int i = 0; i + 2 < l; i += 3) {
        const char t = s[i + 2];
        s[i + 2] = s[i + 1];
        s[i + 1] = s[i];
        s[i] = t;
    }
    return s;
}
