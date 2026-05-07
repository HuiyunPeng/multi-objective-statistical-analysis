#include <string>
#include <cstdio>
using namespace std;

static inline int decimal_length(int n) {
    int len = 1;
    while (n >= 10) {
        n /= 10;
        ++len;
    }
    return len;
}

string change_base(int x, int base) {
    if (x <= 0) return "";

    int remainders[sizeof(int) * 8];
    int count = 0;
    size_t total_len = 0;

    while (x > 0) {
        int r = x % base;
        remainders[count++] = r;
        total_len += decimal_length(r);
        x /= base;
    }

    string out;
    out.reserve(total_len);

    char buf[12];
    for (int i = count - 1; i >= 0; --i) {
        int len = snprintf(buf, sizeof(buf), "%d", remainders[i]);
        out.append(buf, static_cast<size_t>(len));
    }

    return out;
}
