#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    if (number <= 0) return "";

    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char* symbols[] = {"m", "cm", "d", "cd", "c", "xc", "l", "xl", "x", "ix", "v", "iv", "i"};

    string current;
    current.reserve(number / 1000 + 16);

    for (int i = 0; i < 13 && number > 0; ++i) {
        int count = number / values[i];
        number %= values[i];
        while (count-- > 0) {
            current += symbols[i];
        }
    }

    return current;
}
