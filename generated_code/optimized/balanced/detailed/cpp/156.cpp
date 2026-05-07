#include <string>
using namespace std;

string int_to_mini_romank(int number) {
    if (number <= 0) return string();

    static const char* const hundreds[] = {
        "", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"
    };
    static const char* const tens[] = {
        "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"
    };
    static const char* const ones[] = {
        "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"
    };

    static const unsigned char hundreds_len[] = {0,1,2,3,2,1,2,3,4,2};
    static const unsigned char tens_len[]     = {0,1,2,3,2,1,2,3,4,2};
    static const unsigned char ones_len[]     = {0,1,2,3,2,1,2,3,4,2};

    const int thousands = number / 1000;
    number %= 1000;
    const int h = number / 100;
    number %= 100;
    const int t = number / 10;
    const int o = number % 10;

    string result;
    result.reserve(static_cast<size_t>(thousands) +
                   hundreds_len[h] + tens_len[t] + ones_len[o]);

    result.append(static_cast<size_t>(thousands), 'm');
    result.append(hundreds[h], hundreds_len[h]);
    result.append(tens[t], tens_len[t]);
    result.append(ones[o], ones_len[o]);

    return result;
}
