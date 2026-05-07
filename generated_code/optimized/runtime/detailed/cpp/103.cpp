#include <string>
#include <algorithm>

std::string rounded_avg(int n, int m) {
    if (n > m) return "-1";

    int num = (m + n) / 2;
    if (num <= 0) return "";

    std::string out;
    out.reserve(32);

    while (num > 0) {
        out.push_back(static_cast<char>('0' + (num & 1)));
        num >>= 1;
    }

    std::reverse(out.begin(), out.end());
    return out;
}
