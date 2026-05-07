#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    if (number <= 0) return "";

    static const char* hundreds[] = {
        "", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"
    };
    static const char* tens[] = {
        "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"
    };
    static const char* ones[] = {
        "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"
    };

    const int thousands = number / 1000;
    number %= 1000;

    string result;
    result.reserve(thousands + 8);

    if (thousands > 0) result.append(thousands, 'm');
    result += hundreds[number / 100];
    number %= 100;
    result += tens[number / 10];
    result += ones[number % 10];

    return result;
}
