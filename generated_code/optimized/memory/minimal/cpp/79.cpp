#include <string>
using namespace std;

string decimal_to_binary(int decimal) {
    if (decimal == 0) return "db0db";
    if (decimal < 0) return "dbdb";

    int bits = 0;
    for (int temp = decimal; temp > 0; temp >>= 1) ++bits;

    string out;
    out.reserve(bits + 4);
    out += "db";
    for (int i = bits - 1; i >= 0; --i) {
        out += char('0' + ((decimal >> i) & 1));
    }
    out += "db";
    return out;
}
