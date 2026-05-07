#include <string>

using std::string;

bool prime_length(string str) {
    const size_t n = str.size();
    if (n <= 1) return false;
    if (n <= 3) return true;
    if ((n & 1u) == 0 || n % 3 == 0) return false;

    for (size_t i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
