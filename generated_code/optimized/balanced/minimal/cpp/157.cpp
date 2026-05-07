#include <cmath>

bool right_angle_triangle(float a, float b, float c) {
    const float aa = a * a;
    const float bb = b * b;
    const float cc = c * c;

    float hyp = aa;
    float sum = bb + cc;

    if (bb > hyp) {
        hyp = bb;
        sum = aa + cc;
    }
    if (cc > hyp) {
        hyp = cc;
        sum = aa + bb;
    }

    return std::fabs(sum - hyp) < 1e-4f;
}
