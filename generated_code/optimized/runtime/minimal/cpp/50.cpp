#include <string>
using namespace std;

string encode_shift(string s) {
    for (char &c : s) {
        c = static_cast<char>((static_cast<int>(c) + 5 - static_cast<int>('a')) % 26 + static_cast<int>('a'));
    }
    return s;
}

string decode_shift(string s) {
    for (char &c : s) {
        c = static_cast<char>((static_cast<int>(c) + 21 - static_cast<int>('a')) % 26 + static_cast<int>('a'));
    }
    return s;
}
