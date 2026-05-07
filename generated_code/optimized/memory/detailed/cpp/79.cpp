#include <string>
using namespace std;

string decimal_to_binary(int decimal) {
    if (decimal == 0) return "db0db";
    if (decimal < 0) return "dbdb";

    int temp = decimal;
    size_t bits = 0;
    while (temp > 0) {
        ++bits;
        temp /= 2;
    }

    string out(bits + 4, '0');
    out[0] = 'd';
    out[1] = 'b';
    out[bits + 2] = 'd';
    out[bits + 3] = 'b';

    for (size_t i = bits + 1; decimal > 0; --i) {
        out[i] = (decimal & 1) ? '1' : '0';
        decimal /= 2;
    }

    return out;
}
