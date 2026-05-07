#include <string>
using namespace std;

bool valid_date(string date) {
    if (date.size() != 10) return false;

    const char* s = date.c_str();

    if (s[2] != '-' || s[5] != '-') return false;

    if ((unsigned)(s[0] - '0') > 9 || (unsigned)(s[1] - '0') > 9 ||
        (unsigned)(s[3] - '0') > 9 || (unsigned)(s[4] - '0') > 9 ||
        (unsigned)(s[6] - '0') > 9 || (unsigned)(s[7] - '0') > 9 ||
        (unsigned)(s[8] - '0') > 9 || (unsigned)(s[9] - '0') > 9) {
        return false;
    }

    const int mm = (s[0] - '0') * 10 + (s[1] - '0');
    const int dd = (s[3] - '0') * 10 + (s[4] - '0');

    if (mm < 1 || mm > 12) return false;
    if (dd < 1 || dd > 31) return false;
    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11 || mm == 2)) return false;
    if (dd == 30 && mm == 2) return false;

    return true;
}
