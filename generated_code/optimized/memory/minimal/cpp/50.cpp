#include <string>
using namespace std;

string encode_shift(string s) {
    for (char &c : s) {
        c = char((c - 'a' + 5) % 26 + 'a');
    }
    return s;
}

string decode_shift(string s) {
    for (char &c : s) {
        c = char((c - 'a' + 21) % 26 + 'a');
    }
    return s;
}
