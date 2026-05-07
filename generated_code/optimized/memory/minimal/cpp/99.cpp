#include <string>
#include <cstdlib>
#include <cmath>

using std::string;

int closest_integer(string value) {
    return static_cast<int>(std::lround(std::strtod(value.c_str(), nullptr)));
}
