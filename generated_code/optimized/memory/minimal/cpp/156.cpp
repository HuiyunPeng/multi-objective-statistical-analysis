#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char* symbols[] = {"m", "cm", "d", "cd", "c", "xc", "l", "xl", "x", "ix", "v", "iv", "i"};

    string current;
    for (int i = 0; i < 13 && number > 0; ++i) {
        while (number >= values[i]) {
            current += symbols[i];
            number -= values[i];
        }
    }
    return current;
}
