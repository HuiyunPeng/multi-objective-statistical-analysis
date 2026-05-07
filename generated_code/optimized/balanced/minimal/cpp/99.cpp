#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <climits>

using std::string;

int closest_integer(string value) {
    const char* s = value.c_str();
    size_t i = 0, n = value.size();

    while (i < n && std::isspace(static_cast<unsigned char>(s[i]))) ++i;

    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        if (s[i] == '-') sign = -1;
        ++i;
    }

    long long int_part = 0;
    bool has_digit = false;
    bool overflow = false;

    while (i < n && s[i] >= '0' && s[i] <= '9') {
        has_digit = true;
        int digit = s[i] - '0';
        if (int_part > (LLONG_MAX - digit) / 10) {
            overflow = true;
            break;
        }
        int_part = int_part * 10 + digit;
        ++i;
    }

    int first_frac_digit = 0;
    if (!overflow && i < n && s[i] == '.') {
        ++i;
        if (i < n && s[i] >= '0' && s[i] <= '9') {
            first_frac_digit = s[i] - '0';
            has_digit = true;
            ++i;
        }
        while (i < n && s[i] >= '0' && s[i] <= '9') ++i;
    }

    while (!overflow && i < n && std::isspace(static_cast<unsigned char>(s[i]))) ++i;

    if (!overflow && has_digit && i == n) {
        long long result = int_part + (first_frac_digit >= 5);
        return static_cast<int>(sign < 0 ? -result : result);
    }

    return static_cast<int>(std::round(std::strtod(value.c_str(), nullptr)));
}
