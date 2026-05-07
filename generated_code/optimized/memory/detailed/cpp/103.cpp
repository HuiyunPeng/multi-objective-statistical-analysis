#include <string>
using namespace std;

string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    int num = (m + n) / 2;
    if (num <= 0) return "";

    int bits = 0;
    for (int x = num; x > 0; x >>= 1) {
        ++bits;
    }

    string out(bits, '0');
    for (int i = bits - 1; i >= 0; --i) {
        out[i] = char('0' + (num & 1));
        num >>= 1;
    }

    return out;
}
