#include <string>
#include <charconv>

using namespace std;

string string_sequence(int n) {
    if (n <= 0) return "0";

    size_t total = 1; // "0"
    long long start = 1;
    int digits = 1;

    while (start <= n) {
        long long end = start * 10 - 1;
        if (end > n) end = n;
        total += static_cast<size_t>(end - start + 1) * static_cast<size_t>(digits + 1); // space + digits
        start *= 10;
        ++digits;
    }

    string out;
    out.reserve(total);
    out.push_back('0');

    char buf[16];
    for (int i = 1; i <= n; ++i) {
        out.push_back(' ');
        auto res = to_chars(buf, buf + sizeof(buf), i);
        out.append(buf, res.ptr);
    }

    return out;
}
