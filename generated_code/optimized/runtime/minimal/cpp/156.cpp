#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    if (number <= 0) return "";

    static const string hundreds[] = {
        "", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"
    };
    static const string tens[] = {
        "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"
    };
    static const string ones[] = {
        "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"
    };

    int thousands = number / 1000;
    number %= 1000;

    string result;
    result.reserve(thousands + 12);
    result.append(thousands, 'm');
    result += hundreds[number / 100];
    number %= 100;
    result += tens[number / 10];
    result += ones[number % 10];

    return result;
}
