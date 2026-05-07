#include <string>
using namespace std;

bool prime_length(string str) {
    const size_t n = str.size();
    if (n < 2) return false;
    if ((n & 1) == 0) return n == 2;
    if (n % 3 == 0) return n == 3;

    for (size_t i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
