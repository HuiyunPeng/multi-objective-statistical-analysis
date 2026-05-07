#include <cmath>

bool right_angle_triangle(float a, float b, float c) {
    const float aa = a * a, bb = b * b, cc = c * c;
    return std::fabs(aa + bb - cc) < 1e-4f ||
           std::fabs(aa + cc - bb) < 1e-4f ||
           std::fabs(bb + cc - aa) < 1e-4f;
}
