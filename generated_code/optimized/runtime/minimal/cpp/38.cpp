#include <string>
using namespace std;

string encode_cyclic(string s){
    const int l = static_cast<int>(s.length());
    for (int i = 0; i + 2 < l; i += 3) {
        char a = s[i];
        s[i] = s[i + 1];
        s[i + 1] = s[i + 2];
        s[i + 2] = a;
    }
    return s;
}

string decode_cyclic(string s){
    const int l = static_cast<int>(s.length());
    for (int i = 0; i + 2 < l; i += 3) {
        char c = s[i + 2];
        s[i + 2] = s[i + 1];
        s[i + 1] = s[i];
        s[i] = c;
    }
    return s;
}
