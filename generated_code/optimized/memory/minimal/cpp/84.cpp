#include <string>
using namespace std;

string solve(int N) {
    long long x = N;
    if (x < 0) x = -x;

    int sum = 0;
    do {
        sum += static_cast<int>(x % 10);
        x /= 10;
    } while (x);

    if (sum == 0) return "0";

    char buf[32];
    int pos = 31;
    buf[pos] = '\0';

    while (sum > 0) {
        buf[--pos] = static_cast<char>('0' + (sum & 1));
        sum >>= 1;
    }

    return string(buf + pos);
}
