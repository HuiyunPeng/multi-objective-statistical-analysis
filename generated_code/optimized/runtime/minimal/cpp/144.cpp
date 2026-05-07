#include <string>
using std::string;

static inline void parseFraction(const string& s, long long& num, long long& den) {
    const char* p = s.c_str();

    long long sign = 1;
    if (*p == '-') {
        sign = -1;
        ++p;
    } else if (*p == '+') {
        ++p;
    }

    long long value = 0;
    while (*p != '/') {
        value = value * 10 + (*p - '0');
        ++p;
    }
    num = sign * value;

    ++p;
    sign = 1;
    if (*p == '-') {
        sign = -1;
        ++p;
    } else if (*p == '+') {
        ++p;
    }

    value = 0;
    while (*p) {
        value = value * 10 + (*p - '0');
        ++p;
    }
    den = sign * value;
}

bool simplify(string x, string n) {
    long long a, b, c, d;
    parseFraction(x, a, b);
    parseFraction(n, c, d);
    return ((a * c) % (b * d)) == 0;
}
