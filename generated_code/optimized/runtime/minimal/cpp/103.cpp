#include <string>
using namespace std;

string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    unsigned int num = static_cast<unsigned int>((n + m) >> 1);
    if (num == 0) return "";

    int bits = 0;
    unsigned int temp = num;
    while (temp) {
        ++bits;
        temp >>= 1;
    }

    string out(bits, '0');
    for (int i = bits - 1; i >= 0; --i) {
        out[i] = static_cast<char>('0' + (num & 1u));
        num >>= 1;
    }
    return out;
}
