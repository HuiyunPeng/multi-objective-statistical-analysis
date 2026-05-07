#include <string>
#include <cstdlib>
#include <cmath>

int closest_integer(std::string value) {
    return static_cast<int>(std::lround(std::strtod(value.c_str(), nullptr)));
}
