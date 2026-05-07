#include <cmath>

bool iscuber(int a) {
    long long x = a;
    if (x < 0) x = -x;

    int r = static_cast<int>(std::cbrt(static_cast<double>(x)));

    long long c = 1LL * r * r * r;
    if (c == x) return true;

    ++r;
    c = 1LL * r * r * r;
    if (c == x) return true;

    r -= 2;
    if (r >= 0) {
        c = 1LL * r * r * r;
        if (c == x) return true;
    }

    return false;
}
