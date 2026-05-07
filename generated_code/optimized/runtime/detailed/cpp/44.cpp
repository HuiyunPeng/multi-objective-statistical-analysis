#include <string>
#include <vector>
#include <charconv>

using namespace std;

string change_base(int x, int base) {
    if (x <= 0) return "";

    vector<int> digits;
    digits.reserve(32);

    while (x > 0) {
        digits.push_back(x % base);
        x /= base;
    }

    string out;
    out.reserve(digits.size() * 11);

    char buf[16];
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        auto res = to_chars(buf, buf + sizeof(buf), *it);
        out.append(buf, res.ptr);
    }

    return out;
}
