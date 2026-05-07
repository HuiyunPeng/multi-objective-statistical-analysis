#include <string>
#include <climits>
#include <cstring>
using namespace std;

string decimal_to_binary(int decimal) {
    if (decimal == 0) return "db0db";

    constexpr int kBits = sizeof(unsigned int) * CHAR_BIT;
    char bits[kBits];
    int pos = kBits;

    if (decimal > 0) {
        unsigned int value = static_cast<unsigned int>(decimal);
        while (value != 0) {
            bits[--pos] = static_cast<char>('0' + (value & 1u));
            value >>= 1;
        }
    }

    const int len = kBits - pos;
    string out;
    out.resize(len + 4);
    out[0] = 'd';
    out[1] = 'b';
    if (len > 0) {
        memcpy(&out[2], bits + pos, static_cast<size_t>(len));
    }
    out[len + 2] = 'd';
    out[len + 3] = 'b';
    return out;
}
