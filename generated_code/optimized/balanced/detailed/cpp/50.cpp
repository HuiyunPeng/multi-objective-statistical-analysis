#include <string>
using namespace std;

string encode_shift(string s) {
    const size_t n = s.size();
    for (size_t i = 0; i < n; ++i) {
        s[i] = static_cast<char>((s[i] - 'a' + 5) % 26 + 'a');
    }
    return s;
}

string decode_shift(string s) {
    const size_t n = s.size();
    for (size_t i = 0; i < n; ++i) {
        s[i] = static_cast<char>((s[i] - 'a' + 21) % 26 + 'a');
    }
    return s;
}
