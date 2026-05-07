#include <cmath>

bool any_int(float a, float b, float c) {
    if (std::trunc(a) != a || std::trunc(b) != b || std::trunc(c) != c) {
        return false;
    }

    const float ab = a + b;
    const float ac = a + c;
    const float bc = b + c;

    return (ab == c) || (ac == b) || (bc == a);
}
