#include <string>
using namespace std;

string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    const long long sum = static_cast<long long>(n) + static_cast<long long>(m);
    int num = static_cast<int>(sum / 2);

    if (num <= 0) return "";

    char buf[sizeof(int) * 8];
    int idx = sizeof(buf);

    unsigned int x = static_cast<unsigned int>(num);
    while (x) {
        buf[--idx] = static_cast<char>('0' + (x & 1u));
        x >>= 1;
    }

    return string(buf + idx, sizeof(buf) - idx);
}
