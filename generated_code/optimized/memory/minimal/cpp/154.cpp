#include <string>
using namespace std;

bool cycpattern_check(string a, string b) {
    const size_t n = a.size();
    const size_t m = b.size();

    if (m == 0 || m > n) return false;

    for (size_t i = 0; i + m <= n; ++i) {
        for (size_t shift = 0; shift < m; ++shift) {
            if (a[i] != b[shift]) continue;

            size_t k = 1;
            while (k < m && a[i + k] == b[(shift + k < m) ? (shift + k) : (shift + k - m)]) {
                ++k;
            }

            if (k == m) return true;
        }
    }

    return false;
}
