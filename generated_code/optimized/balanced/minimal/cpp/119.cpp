#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    const string& a = lst[0];
    const string& b = lst[1];

    auto analyze = [](const string& s, int& balance, int& min_prefix) {
        balance = 0;
        min_prefix = 0;
        for (char c : s) {
            if (c == '(') ++balance;
            else if (c == ')') --balance;
            if (balance < min_prefix) min_prefix = balance;
        }
    };

    int bal_a, min_a, bal_b, min_b;
    analyze(a, bal_a, min_a);
    analyze(b, bal_b, min_b);

    if (bal_a + bal_b != 0) return "No";

    if ((min_a >= 0 && bal_a + min_b >= 0) ||
        (min_b >= 0 && bal_b + min_a >= 0)) {
        return "Yes";
    }

    return "No";
}
