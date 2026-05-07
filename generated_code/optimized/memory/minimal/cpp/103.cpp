#include <string>
using namespace std;

string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    long long sum = (long long)n + m;
    int num = (int)(sum / 2);

    if (num <= 0) return "";

    int bits = 0;
    for (int t = num; t > 0; t >>= 1) ++bits;

    string out(bits, '0');
    while (num > 0) {
        out[--bits] = char('0' + (num & 1));
        num >>= 1;
    }

    return out;
}
