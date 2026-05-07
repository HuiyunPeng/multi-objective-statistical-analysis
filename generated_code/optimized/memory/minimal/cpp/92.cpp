#include <cmath>

bool any_int(float a, float b, float c) {
    if (std::round(a) != a || std::round(b) != b || std::round(c) != c)
        return false;
    return a + b == c || a + c == b || b + c == a;
}
