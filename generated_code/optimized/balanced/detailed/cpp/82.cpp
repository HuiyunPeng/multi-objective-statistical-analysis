#include <string>

bool prime_length(std::string str) {
    const int l = static_cast<int>(str.size());
    if (l < 2) return false;
    if ((l & 1) == 0) return l == 2;
    for (int i = 3; i <= l / i; i += 2) {
        if (l % i == 0) return false;
    }
    return true;
}
