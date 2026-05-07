#include <string>
using namespace std;

string encode_shift(string s) {
    const size_t n = s.size();
    string out(n, '\0');
    for (size_t i = 0; i < n; ++i) {
        out[i] = char(((s[i] - 'a' + 5) % 26) + 'a');
    }
    return out;
}

string decode_shift(string s) {
    const size_t n = s.size();
    string out(n, '\0');
    for (size_t i = 0; i < n; ++i) {
        out[i] = char(((s[i] - 'a' + 21) % 26) + 'a');
    }
    return out;
}
