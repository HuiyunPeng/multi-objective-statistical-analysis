#include <string>
using namespace std;

static inline size_t decimal_len(unsigned int v) {
    if (v >= 1000000000u) return 10;
    if (v >= 100000000u) return 9;
    if (v >= 10000000u) return 8;
    if (v >= 1000000u) return 7;
    if (v >= 100000u) return 6;
    if (v >= 10000u) return 5;
    if (v >= 1000u) return 4;
    if (v >= 100u) return 3;
    if (v >= 10u) return 2;
    return 1;
}

static inline void append_uint(string& s, unsigned int v) {
    char buf[10];
    int n = 0;
    do {
        buf[n++] = char('0' + (v % 10));
        v /= 10;
    } while (v);

    while (n--) s.push_back(buf[n]);
}

string change_base(int x, int base) {
    if (x <= 0) return "";

    unsigned int rems[33];
    int count = 0;

    while (x > 0) {
        rems[count++] = static_cast<unsigned int>(x % base);
        x /= base;
    }

    size_t total_len = 0;
    for (int i = 0; i < count; ++i) {
        total_len += decimal_len(rems[i]);
    }

    string out;
    out.reserve(total_len);

    for (int i = count - 1; i >= 0; --i) {
        append_uint(out, rems[i]);
    }

    return out;
}
