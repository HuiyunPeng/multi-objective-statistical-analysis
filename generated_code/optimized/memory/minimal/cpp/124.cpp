#include <string>
using namespace std;

bool valid_date(string date) {
    if (date.size() != 10) return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) {
            if (date[i] != '-') return false;
        } else {
            if (date[i] < '0' || date[i] > '9') return false;
        }
    }

    int mm = (date[0] - '0') * 10 + (date[1] - '0');
    int dd = (date[3] - '0') * 10 + (date[4] - '0');
    int yy = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
    (void)yy;

    if (mm < 1 || mm > 12) return false;
    if (dd < 1 || dd > 31) return false;
    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11 || mm == 2)) return false;
    if (dd == 30 && mm == 2) return false;

    return true;
}
