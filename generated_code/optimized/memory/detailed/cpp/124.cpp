#include <string>
using namespace std;

bool valid_date(string date) {
    if (date.size() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }

    const int mm = (date[0] - '0') * 10 + (date[1] - '0');
    const int dd = (date[3] - '0') * 10 + (date[4] - '0');

    if (mm < 1 || mm > 12) return false;
    if (dd < 1 || dd > 31) return false;
    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11 || mm == 2)) return false;
    if (dd == 30 && mm == 2) return false;

    return true;
}
