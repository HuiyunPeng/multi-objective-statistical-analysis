#include <string>
#include <charconv>

using namespace std;

static inline size_t digit_count(unsigned int v) {
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

string change_base(int x, int base) {
    if (x <= 0) return "";

    unsigned int parts[sizeof(int) * 8];
    int count = 0;
    size_t total_len = 0;

    while (x > 0) {
        unsigned int rem = static_cast<unsigned int>(x % base);
        parts[count++] = rem;
        total_len += digit_count(rem);
        x /= base;
    }

    string out;
    out.reserve(total_len);

    char buf[16];
    for (int i = count - 1; i >= 0; --i) {
        auto res = to_chars(buf, buf + sizeof(buf), parts[i]);
        out.append(buf, res.ptr);
    }

    return out;
}
