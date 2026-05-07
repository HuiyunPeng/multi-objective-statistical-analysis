#include <string>

bool is_happy(std::string s) {
    const size_t n = s.size();
    if (n < 3) return false;

    for (size_t i = 2; i < n; ++i) {
        if (s[i] == s[i - 1] || s[i] == s[i - 2]) return false;
    }
    return true;
}
