#include <cmath>

bool right_angle_triangle(float a, float b, float c) {
    const float aa = a * a;
    const float bb = b * b;
    const float cc = c * c;

    float max_sq = aa;
    float other_sum = bb + cc;

    if (bb > max_sq) {
        max_sq = bb;
        other_sum = aa + cc;
    }
    if (cc > max_sq) {
        max_sq = cc;
        other_sum = aa + bb;
    }

    return std::fabs(other_sum - max_sq) < 1e-4f;
}
