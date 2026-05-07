#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>

using namespace std;

int closest_integer(string value) {
    const char* s = value.c_str();

    while (isspace(static_cast<unsigned char>(*s))) ++s;

    bool neg = false;
    if (*s == '+' || *s == '-') {
        neg = (*s == '-');
        ++s;
    }

    long long intPart = 0;
    int digits = 0;
    bool hasDigit = false;

    while (*s >= '0' && *s <= '9') {
        hasDigit = true;
        if (digits < 18) {
            intPart = intPart * 10 + (*s - '0');
            ++digits;
            ++s;
        } else {
            return static_cast<int>(round(strtod(value.c_str(), nullptr)));
        }
    }

    bool roundUp = false;

    if (*s == '.') {
        ++s;
        if (*s >= '0' && *s <= '9') {
            if (*s > '5') {
                roundUp = true;
            } else if (*s == '5') {
                roundUp = true;
                ++s;
                while (*s >= '0' && *s <= '9') ++s;
                while (isspace(static_cast<unsigned char>(*s))) ++s;
                if (*s != '\0') {
                    return static_cast<int>(round(strtod(value.c_str(), nullptr)));
                }
                long long res = intPart + 1;
                return neg ? -static_cast<int>(res) : static_cast<int>(res);
            }
            ++s;
            while (*s >= '0' && *s <= '9') ++s;
        }
    }

    while (isspace(static_cast<unsigned char>(*s))) ++s;
    if (*s != '\0' || !hasDigit) {
        return static_cast<int>(round(strtod(value.c_str(), nullptr)));
    }

    long long res = intPart + (roundUp ? 1 : 0);
    return neg ? -static_cast<int>(res) : static_cast<int>(res);
}
