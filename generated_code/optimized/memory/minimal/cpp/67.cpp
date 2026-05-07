#include <string>
using namespace std;

int fruit_distribution(string s, int n) {
    int num1 = 0, num2 = 0;
    int found = 0;
    bool inNumber = false;

    for (int i = 0; i < (int)s.size() && found < 2; ++i) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            inNumber = true;
            if (found == 0) {
                num1 = num1 * 10 + (c - '0');
            } else {
                num2 = num2 * 10 + (c - '0');
            }
        } else if (inNumber) {
            ++found;
            inNumber = false;
        }
    }

    if (inNumber) ++found;

    return n - num1 - num2;
}
