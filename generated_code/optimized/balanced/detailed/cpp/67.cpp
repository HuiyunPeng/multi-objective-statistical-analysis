#include <string>
using namespace std;

int fruit_distribution(string s, int n) {
    int num1 = 0, num2 = 0;
    bool first_started = false, second_phase = false;

    for (char c : s) {
        if (c >= '0' && c <= '9') {
            if (!second_phase) {
                first_started = true;
                num1 = num1 * 10 + (c - '0');
            } else {
                num2 = num2 * 10 + (c - '0');
            }
        } else if (first_started && !second_phase) {
            second_phase = true;
        }
    }

    return n - num1 - num2;
}
