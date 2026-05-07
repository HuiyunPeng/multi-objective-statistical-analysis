#include <string>
using namespace std;

string file_name_check(string file_name) {
    const size_t n = file_name.size();
    if (n < 5) return "No";

    const char first = file_name[0];
    if (!((first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z')))
        return "No";

    const size_t ext_pos = n - 4;
    if (file_name[ext_pos] != '.') return "No";

    const char c1 = file_name[ext_pos + 1];
    const char c2 = file_name[ext_pos + 2];
    const char c3 = file_name[ext_pos + 3];
    if (!((c1 == 't' && c2 == 'x' && c3 == 't') ||
          (c1 == 'e' && c2 == 'x' && c3 == 'e') ||
          (c1 == 'd' && c2 == 'l' && c3 == 'l')))
        return "No";

    int digit_count = 0;
    for (size_t i = 0; i < ext_pos; ++i) {
        const char ch = file_name[i];
        if (ch == '.') return "No";
        if (ch >= '0' && ch <= '9' && ++digit_count > 3) return "No";
    }

    return "Yes";
}
