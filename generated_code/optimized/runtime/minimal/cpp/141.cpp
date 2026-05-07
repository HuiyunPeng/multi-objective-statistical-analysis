#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t n = file_name.size();
    if (n < 5) return "No";

    const char c0 = file_name[0];
    if (!((c0 >= 'A' && c0 <= 'Z') || (c0 >= 'a' && c0 <= 'z'))) return "No";

    const size_t e = n - 4;
    if (file_name[e] != '.' ||
        !((file_name[e + 1] == 't' && file_name[e + 2] == 'x' && file_name[e + 3] == 't') ||
          (file_name[e + 1] == 'e' && file_name[e + 2] == 'x' && file_name[e + 3] == 'e') ||
          (file_name[e + 1] == 'd' && file_name[e + 2] == 'l' && file_name[e + 3] == 'l')))
        return "No";

    int numdigit = 0;
    for (size_t i = 0; i < e; ++i) {
        const char c = file_name[i];
        if (c >= '0' && c <= '9') {
            if (++numdigit > 3) return "No";
        } else if (c == '.') {
            return "No";
        }
    }

    return "Yes";
}
