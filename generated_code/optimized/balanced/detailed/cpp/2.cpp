#include <cmath>

float truncate_number(float number) {
    float integral_part;
    return std::modff(number, &integral_part);
}
