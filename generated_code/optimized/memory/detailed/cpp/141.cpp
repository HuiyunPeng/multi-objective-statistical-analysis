#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t n = file_name.length();
    if (n < 5) return "No";

    const char first = file_name[0];
    if (!((first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z')))
        return "No";

    if (n < 4) return "No";
    const char* ext = file_name.c_str() + n - 4;
    if (!((ext[0] == '.' && ext[1] == 't' && ext[2] == 'x' && ext[3] == 't') ||
          (ext[0] == '.' && ext[1] == 'e' && ext[2] == 'x' && ext[3] == 'e') ||
          (ext[0] == '.' && ext[1] == 'd' && ext[2] == 'l' && ext[3] == 'l')))
        return "No";

    int numdigit = 0, numdot = 0;
    for (size_t i = 0; i < n; ++i) {
        const char c = file_name[i];
        if (c >= '0' && c <= '9') ++numdigit;
        if (c == '.') ++numdot;
    }

    if (numdigit > 3 || numdot != 1) return "No";
    return "Yes";
}
