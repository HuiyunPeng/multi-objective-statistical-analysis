#include <string>
using namespace std;

int fruit_distribution(string s, int n) {
    int num1 = 0, num2 = 0;
    bool second = false, hasFirst = false;

    const int len = static_cast<int>(s.size());
    for (int i = 0; i < len; ++i) {
        const char c = s[i];
        if (c >= '0' && c <= '9') {
            if (!second) {
                num1 = num1 * 10 + (c - '0');
                hasFirst = true;
            } else {
                num2 = num2 * 10 + (c - '0');
            }
        } else if (!second && hasFirst) {
            second = true;
        }
    }

    return n - num1 - num2;
}
