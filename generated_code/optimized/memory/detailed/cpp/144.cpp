#include <string>
using namespace std;

bool simplify(string x, string n) {
    auto parseFraction = [](const string& s, long long& num, long long& den) {
        num = 0;
        den = 0;
        int numSign = 1, denSign = 1;
        bool afterSlash = false;

        for (char ch : s) {
            if (ch == '/') {
                afterSlash = true;
            } else if (ch == '-') {
                if (afterSlash) denSign = -1;
                else numSign = -1;
            } else if (ch == '+') {
                if (afterSlash) denSign = 1;
                else numSign = 1;
            } else if (ch >= '0' && ch <= '9') {
                if (afterSlash) den = den * 10 + (ch - '0');
                else num = num * 10 + (ch - '0');
            }
        }

        num *= numSign;
        den *= denSign;
    };

    long long a, b, c, d;
    parseFraction(x, a, b);
    parseFraction(n, c, d);

    return ((a * c) % (b * d)) == 0;
}
