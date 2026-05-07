#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    if (number <= 0) return string();

    string current;
    current.reserve(static_cast<size_t>(number / 1000) + 12);

    current.append(number / 1000, 'm');
    number %= 1000;

    auto append_digit = [&](int digit, char one, char five, char ten) {
        switch (digit) {
            case 9: current += one; current += ten; break;
            case 8: current += five; current.append(3, one); break;
            case 7: current += five; current.append(2, one); break;
            case 6: current += five; current += one; break;
            case 5: current += five; break;
            case 4: current += one; current += five; break;
            case 3: current.append(3, one); break;
            case 2: current.append(2, one); break;
            case 1: current += one; break;
        }
    };

    append_digit(number / 100, 'c', 'd', 'm');
    number %= 100;

    append_digit(number / 10, 'x', 'l', 'c');
    number %= 10;

    append_digit(number, 'i', 'v', 'x');

    return current;
}
