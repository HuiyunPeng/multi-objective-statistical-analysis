#include <cmath>

bool any_int(float a, float b, float c) {
    const float ra = std::round(a);
    if (ra != a) return false;

    const float rb = std::round(b);
    if (rb != b) return false;

    const float rc = std::round(c);
    if (rc != c) return false;

    return (a + b == c) || (a + c == b) || (b + c == a);
}
