#include <string>
using namespace std;

bool valid_date(string date) {
    if (date.size() != 10 || date[2] != '-' || date[5] != '-') return false;

    const char d0 = date[0], d1 = date[1], d3 = date[3], d4 = date[4];
    const char d6 = date[6], d7 = date[7], d8 = date[8], d9 = date[9];

    if ((unsigned)(d0 - '0') > 9 || (unsigned)(d1 - '0') > 9 ||
        (unsigned)(d3 - '0') > 9 || (unsigned)(d4 - '0') > 9 ||
        (unsigned)(d6 - '0') > 9 || (unsigned)(d7 - '0') > 9 ||
        (unsigned)(d8 - '0') > 9 || (unsigned)(d9 - '0') > 9) {
        return false;
    }

    const int mm = (d0 - '0') * 10 + (d1 - '0');
    const int dd = (d3 - '0') * 10 + (d4 - '0');

    if (mm < 1 || mm > 12 || dd < 1 || dd > 31) return false;
    if (mm == 2) return dd <= 29;
    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) return false;

    return true;
}
