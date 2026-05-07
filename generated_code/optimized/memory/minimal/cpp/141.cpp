#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t n = file_name.size();
    if (n < 5) return "No";

    const char w = file_name[0];
    if (!((w >= 'A' && w <= 'Z') || (w >= 'a' && w <= 'z'))) return "No";

    const bool valid_ext =
        (file_name[n - 4] == '.' && file_name[n - 3] == 't' && file_name[n - 2] == 'x' && file_name[n - 1] == 't') ||
        (file_name[n - 4] == '.' && file_name[n - 3] == 'e' && file_name[n - 2] == 'x' && file_name[n - 1] == 'e') ||
        (file_name[n - 4] == '.' && file_name[n - 3] == 'd' && file_name[n - 2] == 'l' && file_name[n - 1] == 'l');

    if (!valid_ext) return "No";

    int numdigit = 0, numdot = 0;
    for (size_t i = 0; i < n; ++i) {
        const char c = file_name[i];
        if (c >= '0' && c <= '9') ++numdigit;
        if (c == '.') ++numdot;
    }

    if (numdigit > 3 || numdot != 1) return "No";
    return "Yes";
}
