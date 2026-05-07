#include <string>
using namespace std;

string decimal_to_binary(int decimal) {
    if (decimal == 0) return "db0db";
    if (decimal < 0) return "dbdb";

    unsigned int value = static_cast<unsigned int>(decimal);
    unsigned int temp = value;
    int bits = 0;
    while (temp) {
        ++bits;
        temp >>= 1;
    }

    string out(bits + 4, '\0');
    out[0] = 'd';
    out[1] = 'b';
    out[bits + 2] = 'd';
    out[bits + 3] = 'b';

    for (int i = bits + 1; i >= 2; --i) {
        out[i] = static_cast<char>('0' + (value & 1u));
        value >>= 1;
    }

    return out;
}
