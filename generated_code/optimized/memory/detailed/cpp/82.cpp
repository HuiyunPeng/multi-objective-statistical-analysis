#include <string>

bool prime_length(std::string str) {
    const std::string::size_type l = str.size();
    if (l < 2) return false;
    for (std::string::size_type i = 2; i * i <= l; ++i) {
        if (l % i == 0) return false;
    }
    return true;
}
