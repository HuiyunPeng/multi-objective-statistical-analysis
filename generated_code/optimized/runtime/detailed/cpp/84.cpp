#include <string>
using namespace std;

string solve(int N) {
    int sum = 0;

    if (N >= 0) {
        while (N > 0) {
            sum += N % 10;
            N /= 10;
        }
    } else {
        const string str = to_string(N);
        for (char c : str) {
            sum += c - '0';
        }
    }

    if (sum <= 0) return "";

    int mask = 1;
    while (mask <= (sum >> 1)) {
        mask <<= 1;
    }

    string bi;
    bi.reserve(8);
    while (mask > 0) {
        bi.push_back((sum & mask) ? '1' : '0');
        mask >>= 1;
    }

    return bi;
}
