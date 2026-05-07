#include <string>
using namespace std;

static inline size_t decimal_length(int v) {
    size_t len = 1;
    while (v >= 10) {
        v /= 10;
        ++len;
    }
    return len;
}

static inline void append_decimal(int v, string& out) {
    if (v >= 10) {
        append_decimal(v / 10, out);
    }
    out.push_back(static_cast<char>('0' + (v % 10)));
}

static void build_base_string(int x, int base, string& out) {
    if (x >= base) {
        build_base_string(x / base, base, out);
    }
    append_decimal(x % base, out);
}

string change_base(int x, int base) {
    if (x <= 0) {
        return "";
    }

    size_t total_len = 0;
    for (int t = x; t > 0; t /= base) {
        total_len += decimal_length(t % base);
    }

    string out;
    out.reserve(total_len);
    build_base_string(x, base, out);
    return out;
}
