#include <string>
using namespace std;

static inline long long parseInt(const string& s, size_t& i) {
    long long sign = 1, value = 0;
    if (i < s.size() && s[i] == '-') {
        sign = -1;
        ++i;
    } else if (i < s.size() && s[i] == '+') {
        ++i;
    }
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        value = value * 10 + (s[i] - '0');
        ++i;
    }
    return sign * value;
}

bool simplify(string x, string n) {
    size_t i = 0, j = 0;
    long long a = parseInt(x, i);
    ++i; // skip '/'
    long long b = parseInt(x, i);

    long long c = parseInt(n, j);
    ++j; // skip '/'
    long long d = parseInt(n, j);

    return ((a * c) % (b * d)) == 0;
}
