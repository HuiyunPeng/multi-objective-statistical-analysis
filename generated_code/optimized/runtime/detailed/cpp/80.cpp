#include <string>
using namespace std;

bool is_happy(string s) {
    const size_t n = s.size();
    if (n < 3) return false;

    const char* p = s.data();
    for (size_t i = 2; i < n; ++i) {
        const char c = p[i];
        if (c == p[i - 1] || c == p[i - 2]) return false;
    }
    return true;
}
