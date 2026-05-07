#include <string>
using namespace std;

static inline long long gcdll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static inline void parseFraction(const string& s, long long& num, long long& den) {
    const char* p = s.c_str();

    int sign = 1;
    if (*p == '+' || *p == '-') {
        if (*p == '-') sign = -1;
        ++p;
    }

    long long value = 0;
    while (*p && *p != '/') {
        value = value * 10 + (*p - '0');
        ++p;
    }
    num = sign * value;

    if (*p == '/') ++p;

    sign = 1;
    if (*p == '+' || *p == '-') {
        if (*p == '-') sign = -1;
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

    if (b < 0) {
        b = -b;
        a = -a;
    }
    if (d < 0) {
        d = -d;
        c = -c;
    }

    long long g = gcdll(a, b);
    if (g > 1) {
        a /= g;
        b /= g;
    }

    g = gcdll(c, d);
    if (g > 1) {
        c /= g;
        d /= g;
    }

    g = gcdll(a, d);
    if (g > 1) {
        a /= g;
        d /= g;
    }

    g = gcdll(c, b);
    if (g > 1) {
        c /= g;
        b /= g;
    }

    return b == 1 && d == 1;
}
