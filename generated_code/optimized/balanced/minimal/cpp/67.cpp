#include <string>
using namespace std;

int fruit_distribution(string s, int n) {
    int num1 = 0, num2 = 0;
    bool second = false;
    bool seen_first_digit = false;

    for (char c : s) {
        if (c >= '0' && c <= '9') {
            if (!second) {
                num1 = num1 * 10 + (c - '0');
                seen_first_digit = true;
            } else {
                num2 = num2 * 10 + (c - '0');
            }
        } else if (!second && seen_first_digit) {
            second = true;
        }
    }

    return n - num1 - num2;
}
