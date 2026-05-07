#include <string>
using namespace std;

bool prime_length(string str) {
    const int l = static_cast<int>(str.size());
    if (l < 2) return false;
    if (l == 2) return true;
    if ((l & 1) == 0) return false;

    for (int i = 3; i <= l / i; i += 2) {
        if (l % i == 0) return false;
    }
    return true;
}
