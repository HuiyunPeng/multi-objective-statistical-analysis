#include <string>
using namespace std;

string solve(int N) {
    int sum = 0;
    while (N > 0) {
        sum += N % 10;
        N /= 10;
    }

    if (sum == 0) return "";

    char buf[32];
    int pos = 32;

    while (sum > 0) {
        buf[--pos] = char('0' + (sum & 1));
        sum >>= 1;
    }

    return string(buf + pos, 32 - pos);
}
