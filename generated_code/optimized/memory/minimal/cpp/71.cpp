#include <cmath>

float triangle_area(float a, float b, float c) {
    if (a + b <= c || a + c <= b || b + c <= a) return -1.0f;
    float h = (a + b + c) * 0.5f;
    return std::sqrt(h * (h - a) * (h - b) * (h - c));
}
