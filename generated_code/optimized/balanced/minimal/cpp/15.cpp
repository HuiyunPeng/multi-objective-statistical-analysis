#include <string>

using namespace std;

static inline void append_positive_int(string& out, int value) {
    char buf[10];
    int pos = 10;
    do {
        buf[--pos] = static_cast<char>('0' + (value % 10));
        value /= 10;
    } while (value != 0);
    out.append(buf + pos, 10 - pos);
}

string string_sequence(int n) {
    if (n <= 0) return "0";

    size_t total_len = 1 + static_cast<size_t>(n); // "0" + spaces
    long long start = 1;
    int digits = 1;
    while (start <= n) {
        long long next = start * 10;
        long long end = (next - 1 < n) ? (next - 1) : n;
        total_len += static_cast<size_t>(end - start + 1) * static_cast<size_t>(digits);
        start = next;
        ++digits;
    }

    string out;
    out.reserve(total_len);
    out.push_back('0');

    for (int i = 1; i <= n; ++i) {
        out.push_back(' ');
        append_positive_int(out, i);
    }

    return out;
}
