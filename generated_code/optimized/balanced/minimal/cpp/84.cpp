#include <string>
using namespace std;

string solve(int N) {
    long long x = N;
    if (x < 0) x = -x;

    int sum = 0;
    while (x > 0) {
        sum += static_cast<int>(x % 10);
        x /= 10;
    }

    if (sum == 0) return "";

    char buf[16];
    int pos = 16;
    while (sum > 0) {
        buf[--pos] = static_cast<char>('0' + (sum & 1));
        sum >>= 1;
    }

    return string(buf + pos, 16 - pos);
}
