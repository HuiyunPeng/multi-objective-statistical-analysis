#include <string>
#include <charconv>
#include <limits>

using std::string;

string change_base(int x, int base) {
    if (base <= 1) return "";
    if (x == 0) return "0";
    if (x < 0) return "";
    if (base == 10) return std::to_string(x);

    unsigned int value = static_cast<unsigned int>(x);
    const unsigned int base_u = static_cast<unsigned int>(base);

    constexpr size_t kMaxChunkLen = std::numeric_limits<unsigned int>::digits10 + 1;
    constexpr size_t kMaxParts = std::numeric_limits<unsigned int>::digits + 1;
    char buffer[kMaxChunkLen * kMaxParts + 1];
    char* p = buffer + sizeof(buffer);

    do {
        const unsigned int rem = value % base_u;
        value /= base_u;

        char tmp[kMaxChunkLen];
        auto res = std::to_chars(tmp, tmp + kMaxChunkLen, rem);
        for (char* q = res.ptr; q != tmp;) {
            *--p = *--q;
        }
    } while (value != 0);

    return string(p, static_cast<size_t>(buffer + sizeof(buffer) - p));
}
