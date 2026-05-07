#include <string>
using std::string;

bool prime_length(string str) {
    const size_t l = str.size();
    if (l < 2) return false;
    if ((l & 1) == 0) return l == 2;
    for (size_t i = 3; i <= l / i; i += 2) {
        if (l % i == 0) return false;
    }
    return true;
}
