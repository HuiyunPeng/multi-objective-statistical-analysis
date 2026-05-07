#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t len = file_name.size();
    if (len < 5) return "No";

    const char first = file_name[0];
    if (!((first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z')))
        return "No";

    if (file_name[len - 4] != '.')
        return "No";

    const char e1 = file_name[len - 3];
    const char e2 = file_name[len - 2];
    const char e3 = file_name[len - 1];

    if (!((e1 == 't' && e2 == 'x' && e3 == 't') ||
          (e1 == 'e' && e2 == 'x' && e3 == 'e') ||
          (e1 == 'd' && e2 == 'l' && e3 == 'l')))
        return "No";

    int numdigit = 0;
    for (size_t i = 1; i + 4 < len; ++i) {
        const char c = file_name[i];
        if (c == '.')
            return "No";
        if (c >= '0' && c <= '9' && ++numdigit > 3)
            return "No";
    }

    return "Yes";
}
