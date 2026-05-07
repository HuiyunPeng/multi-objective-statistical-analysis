#include <string>
#include <charconv>

using namespace std;

string string_sequence(int n) {
    if (n <= 0) return "0";

    size_t total_len = 1; // "0"
    long long start = 1;

    for (int digits = 1; start <= n; ++digits) {
        long long next = start * 10;
        long long end = (next - 1 < n) ? (next - 1) : n;
        total_len += static_cast<size_t>(end - start + 1) * static_cast<size_t>(digits + 1); // space + digits
        start = next;
    }

    string out;
    out.reserve(total_len);
    out.push_back('0');

    char buf[16];
    for (int i = 1; i <= n; ++i) {
        out.push_back(' ');
        auto res = to_chars(buf, buf + sizeof(buf), i);
        out.append(buf, res.ptr);
    }

    return out;
}
