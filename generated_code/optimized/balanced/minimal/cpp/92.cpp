#include <cmath>

bool any_int(float a, float b, float c) {
    if (std::trunc(a) != a || std::trunc(b) != b || std::trunc(c) != c) {
        return false;
    }
    return a + b == c || a + c == b || b + c == a;
}
