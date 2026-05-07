#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

static inline int parseRange(const string& s, size_t l, size_t r) {
    while (l < r && static_cast<unsigned char>(s[l]) <= ' ') ++l;

    int sign = 1;
    if (l < r && s[l] == '-') {
        sign = -1;
        ++l;
    } else if (l < r && s[l] == '+') {
        ++l;
    }

    int value = 0;
    while (l < r) {
        char ch = s[l];
        if (ch < '0' || ch > '9') break;
        value = value * 10 + (ch - '0');
        ++l;
    }
    return sign * value;
}

bool simplify(string x, string n) {
    const size_t sx = x.find('/');
    const size_t sn = n.find('/');

    const int a = parseRange(x, 0, sx);
    const int b = parseRange(x, sx + 1, x.size());
    const int c = parseRange(n, 0, sn);
    const int d = parseRange(n, sn + 1, n.size());

    return (1LL * a * c) % (1LL * b * d) == 0;
}
