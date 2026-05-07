#include <string>
using namespace std;

static inline long long parsePart(const string& s, size_t l, size_t r) {
    long long sign = 1, value = 0;
    if (l < r && s[l] == '-') {
        sign = -1;
        ++l;
    }
    for (; l < r; ++l) {
        value = value * 10 + (s[l] - '0');
    }
    return sign * value;
}

static inline unsigned long long absll(long long v) {
    return v < 0 ? static_cast<unsigned long long>(-(v + 1)) + 1ULL
                 : static_cast<unsigned long long>(v);
}

static inline unsigned long long gcdll(unsigned long long a, unsigned long long b) {
    while (b) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

bool simplify(string x, string n) {
    const size_t sx = x.find('/');
    const size_t sn = n.find('/');

    const long long a = parsePart(x, 0, sx);
    const long long b = parsePart(x, sx + 1, x.size());
    const long long c = parsePart(n, 0, sn);
    const long long d = parsePart(n, sn + 1, n.size());

    unsigned long long num1 = absll(a);
    unsigned long long den1 = absll(b);
    unsigned long long num2 = absll(c);
    unsigned long long den2 = absll(d);

    if (den1 == 0 || den2 == 0) return false;
    if (num1 == 0 || num2 == 0) return true;

    unsigned long long g;

    g = gcdll(num1, den1); num1 /= g; den1 /= g;
    g = gcdll(num1, den2); num1 /= g; den2 /= g;
    g = gcdll(num2, den1); num2 /= g; den1 /= g;
    g = gcdll(num2, den2); num2 /= g; den2 /= g;

    return den1 == 1 && den2 == 1;
}
