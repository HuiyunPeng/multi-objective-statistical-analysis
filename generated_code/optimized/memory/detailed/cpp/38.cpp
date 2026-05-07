#include <string>
using std::string;

string encode_cyclic(string s){
    for (size_t i = 0; i + 2 < s.size(); i += 3) {
        char c = s[i];
        s[i] = s[i + 1];
        s[i + 1] = s[i + 2];
        s[i + 2] = c;
    }
    return s;
}

string decode_cyclic(string s){
    for (size_t i = 0; i + 2 < s.size(); i += 3) {
        char c = s[i + 2];
        s[i + 2] = s[i + 1];
        s[i + 1] = s[i];
        s[i] = c;
    }
    return s;
}
