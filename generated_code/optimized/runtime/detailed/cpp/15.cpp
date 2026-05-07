#include <string>
#include <charconv>
#include <algorithm>

using namespace std;

string string_sequence(int n) {
    if (n <= 0) return "0";

    size_t total_len = 1; // "0"
    for (int start = 1, digits = 1; start <= n; ++digits) {
        long long next = 1LL * start * 10;
        int end = static_cast<int>(min<long long>(n, next - 1));
        total_len += static_cast<size_t>(end - start + 1) * static_cast<size_t>(digits + 1);
        if (next > n) break;
        start = static_cast<int>(next);
    }

    string out;
    out.reserve(total_len);
    out.push_back('0');

    char buffer[16];
    for (int i = 1; i <= n; ++i) {
        out.push_back(' ');
        auto res = to_chars(buffer, buffer + sizeof(buffer), i);
        out.append(buffer, res.ptr);
    }

    return out;
}
