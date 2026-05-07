#include <string>
#include <cmath>
#include <cstdlib>
#include <climits>

int closest_integer(std::string value) {
    const char* p = value.c_str();
    const char* const end = p + value.size();

    auto is_space = [](char c) noexcept {
        return c == ' ' || (c >= '\t' && c <= '\r');
    };

    while (p < end && is_space(*p)) ++p;

    bool neg = false;
    if (p < end && (*p == '+' || *p == '-')) {
        neg = (*p == '-');
        ++p;
    }

    const unsigned int limit = neg
        ? static_cast<unsigned int>(INT_MAX) + 1u
        : static_cast<unsigned int>(INT_MAX);

    unsigned int intPart = 0;
    bool hasDigits = false;
    bool overflow = false;

    while (p < end && *p >= '0' && *p <= '9') {
        hasDigits = true;
        const unsigned int digit = static_cast<unsigned int>(*p - '0');
        if (intPart > (limit - digit) / 10u) {
            overflow = true;
            break;
        }
        intPart = intPart * 10u + digit;
        ++p;
    }

    bool roundUp = false;
    if (!overflow && p < end && *p == '.') {
        ++p;
        if (p < end && *p >= '0' && *p <= '9') {
            hasDigits = true;
            roundUp = (*p >= '5');
            do {
                ++p;
            } while (p < end && *p >= '0' && *p <= '9');
        }
    }

    if (!overflow && hasDigits && !(p < end && (*p == 'e' || *p == 'E'))) {
        const char* q = p;
        while (q < end && is_space(*q)) ++q;

        if (q == end) {
            const unsigned int absResult = intPart + static_cast<unsigned int>(roundUp);
            if (neg) {
                return absResult == static_cast<unsigned int>(INT_MAX) + 1u
                    ? INT_MIN
                    : -static_cast<int>(absResult);
            }
            return static_cast<int>(absResult);
        }
    }

    return static_cast<int>(std::round(std::strtod(value.c_str(), nullptr)));
}
