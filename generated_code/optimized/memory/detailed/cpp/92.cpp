#include <cmath>

bool any_int(float a, float b, float c) {
    if (std::floor(a) != a || std::floor(b) != b || std::floor(c) != c) return false;
    return a + b == c || a + c == b || b + c == a;
}
