#include <string>
using std::string;

string solve(int N) {
    int sum = 0;
    if (N < 0) N = -N;

    do {
        sum += N % 10;
        N /= 10;
    } while (N);

    if (sum == 0) return "";

    char buf[16];
    int pos = 16;
    while (sum) {
        buf[--pos] = static_cast<char>('0' + (sum & 1));
        sum >>= 1;
    }

    return string(buf + pos, 16 - pos);
}
