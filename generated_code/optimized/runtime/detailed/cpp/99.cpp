#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int closest_integer(string value) {
    const char* orig = value.c_str();
    const char* s = orig;

    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' || *s == '\f' || *s == '\v') {
        ++s;
    }

    bool neg = false;
    if (*s == '+' || *s == '-') {
        neg = (*s == '-');
        ++s;
    }

    long long intPart = 0;
    bool hasAnyDigit = false;

    while (*s >= '0' && *s <= '9') {
        hasAnyDigit = true;
        intPart = intPart * 10 + (*s - '0');
        ++s;
    }

    int firstFracDigit = 0;
    if (*s == '.') {
        ++s;
        if (*s >= '0' && *s <= '9') {
            hasAnyDigit = true;
            firstFracDigit = *s - '0';
            do {
                ++s;
            } while (*s >= '0' && *s <= '9');
        }
    }

    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' || *s == '\f' || *s == '\v') {
        ++s;
    }

    if (hasAnyDigit && *s == '\0') {
        int result = static_cast<int>(intPart);
        return neg ? -result - (firstFracDigit >= 5) : result + (firstFracDigit >= 5);
    }

    return static_cast<int>(round(strtod(orig, nullptr)));
}
