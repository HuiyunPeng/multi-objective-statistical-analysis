#include <cmath>

bool right_angle_triangle(float a, float b, float c) {
    const float aa = a * a;
    const float bb = b * b;
    const float cc = c * c;

    float max_sq = aa;
    float sum_other = bb + cc;

    if (bb > max_sq) {
        max_sq = bb;
        sum_other = aa + cc;
    }
    if (cc > max_sq) {
        max_sq = cc;
        sum_other = aa + bb;
    }

    return std::fabs(sum_other - max_sq) < 1e-4f;
}
