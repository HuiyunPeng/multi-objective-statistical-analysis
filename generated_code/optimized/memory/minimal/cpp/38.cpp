#include <string>
using namespace std;

string encode_cyclic(string s){
    for (size_t i = 0; i + 2 < s.size(); i += 3) {
        char first = s[i];
        s[i] = s[i + 1];
        s[i + 1] = s[i + 2];
        s[i + 2] = first;
    }
    return s;
}

string decode_cyclic(string s){
    for (size_t i = 0; i + 2 < s.size(); i += 3) {
        char last = s[i + 2];
        s[i + 2] = s[i + 1];
        s[i + 1] = s[i];
        s[i] = last;
    }
    return s;
}
