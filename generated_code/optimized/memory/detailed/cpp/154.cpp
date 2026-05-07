#include <string>
#include <cstring>
using namespace std;

bool cycpattern_check(string a, string b) {
    const size_t m = b.size();
    if (m == 0) return false;

    const size_t n = a.size();
    if (m > n) return false;

    const char* ap = a.data();
    const char* bp = b.data();
    const size_t limit = n - m;

    for (size_t shift = 0; shift < m; ++shift) {
        const size_t tail = m - shift;

        for (size_t pos = 0; pos <= limit; ++pos) {
            if (ap[pos] != bp[shift]) continue;

            if (memcmp(ap + pos, bp + shift, tail) == 0 &&
                (shift == 0 || memcmp(ap + pos + tail, bp, shift) == 0)) {
                return true;
            }
        }
    }

    return false;
}
