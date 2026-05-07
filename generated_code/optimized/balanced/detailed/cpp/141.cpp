#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t n = file_name.size();
    if (n < 5) return "No";

    const char first = file_name[0];
    if (!((first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z')))
        return "No";

    int digits = 0;
    for (size_t i = 0; i + 4 < n; ++i) {
        const char c = file_name[i];
        if (c >= '0' && c <= '9') {
            if (++digits > 3) return "No";
        } else if (c == '.') {
            return "No";
        }
    }

    if (file_name[n - 4] != '.') return "No";

    const char c1 = file_name[n - 3];
    const char c2 = file_name[n - 2];
    const char c3 = file_name[n - 1];

    if ((c1 == 't' && c2 == 'x' && c3 == 't') ||
        (c1 == 'e' && c2 == 'x' && c3 == 'e') ||
        (c1 == 'd' && c2 == 'l' && c3 == 'l')) {
        return "Yes";
    }

    return "No";
}
