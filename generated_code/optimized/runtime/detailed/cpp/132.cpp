#include <string>
using namespace std;

bool is_nested(string str) {
    const size_t n = str.size();
    if (n < 4) return false;

    const char* s = str.data();
    int count = 0, maxcount = 0;

    for (size_t i = 0; i < n; ++i) {
        const char c = s[i];

        if (c == '[') {
            ++count;
            if (count > maxcount) maxcount = count;
        } else if (c == ']') {
            if (count > 0) --count;
        }

        if (count + 2 <= maxcount) return true;
    }

    return false;
}
