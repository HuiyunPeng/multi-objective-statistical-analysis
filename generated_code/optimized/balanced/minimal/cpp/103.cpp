#include <string>
using std::string;

string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    long long avg = (static_cast<long long>(n) + static_cast<long long>(m)) / 2;
    if (avg <= 0) return "";

    char buf[sizeof(long long) * 8];
    int pos = sizeof(buf);

    unsigned long long x = static_cast<unsigned long long>(avg);
    while (x > 0) {
        buf[--pos] = static_cast<char>('0' + (x & 1ULL));
        x >>= 1;
    }

    return string(buf + pos, sizeof(buf) - pos);
}
