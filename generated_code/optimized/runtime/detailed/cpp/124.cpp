#include <string>
using namespace std;

bool valid_date(string date) {
    if (date.size() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    if ((unsigned)(date[0] - '0') > 9 || (unsigned)(date[1] - '0') > 9 ||
        (unsigned)(date[3] - '0') > 9 || (unsigned)(date[4] - '0') > 9 ||
        (unsigned)(date[6] - '0') > 9 || (unsigned)(date[7] - '0') > 9 ||
        (unsigned)(date[8] - '0') > 9 || (unsigned)(date[9] - '0') > 9) {
        return false;
    }

    const int mm = (date[0] - '0') * 10 + (date[1] - '0');
    const int dd = (date[3] - '0') * 10 + (date[4] - '0');

    if ((unsigned)(mm - 1) >= 12 || (unsigned)(dd - 1) >= 31) return false;

    if (mm == 2) return dd <= 29;
    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) return false;

    return true;
}
