#include <string>
using namespace std;

string solve(int N) {
    int sum = 0;
    while (N > 0) {
        sum += N % 10;
        N /= 10;
    }

    if (sum == 0) return "";

    int bits = 0, temp = sum;
    while (temp > 0) {
        ++bits;
        temp >>= 1;
    }

    string bi(bits, '0');
    for (int i = bits - 1; i >= 0; --i) {
        bi[i] = char('0' + (sum & 1));
        sum >>= 1;
    }

    return bi;
}
