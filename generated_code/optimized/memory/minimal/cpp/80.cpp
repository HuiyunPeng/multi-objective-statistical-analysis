#include <string>
using namespace std;

bool is_happy(string s) {
    if (s.size() < 3) return false;
    for (size_t i = 2, n = s.size(); i < n; ++i) {
        if (s[i] == s[i - 1] || s[i] == s[i - 2]) return false;
    }
    return true;
}
