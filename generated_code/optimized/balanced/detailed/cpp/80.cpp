#include <string>

using std::string;

bool is_happy(string s) {
    const size_t n = s.size();
    if (n < 3) return false;

    const char* p = s.data();
    char prev2 = p[0], prev1 = p[1];

    for (size_t i = 2; i < n; ++i) {
        const char c = p[i];
        if (c == prev1 || c == prev2) return false;
        prev2 = prev1;
        prev1 = c;
    }

    return true;
}
