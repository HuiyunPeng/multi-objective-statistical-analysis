#include <string>
#include <charconv>

using namespace std;

string string_sequence(int n) {
    size_t total_len = 1; // "0"

    for (int i = 1; i <= n; ++i) {
        int x = i;
        size_t digits = 1;
        while (x >= 10) {
            x /= 10;
            ++digits;
        }
        total_len += 1 + digits; // space + number
    }

    string out;
    out.reserve(total_len);
    out = '0';

    for (int i = 1; i <= n; ++i) {
        out.push_back(' ');
        char buf[16];
        auto res = to_chars(buf, buf + sizeof(buf), i);
        out.append(buf, res.ptr);
    }

    return out;
}
