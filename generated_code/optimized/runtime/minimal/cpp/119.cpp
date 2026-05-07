#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    auto analyze = [](const string& s, int& balance, int& min_prefix) {
        balance = 0;
        min_prefix = 0;
        for (char c : s) {
            if (c == '(') ++balance;
            else if (c == ')') --balance;
            if (balance < min_prefix) min_prefix = balance;
        }
    };

    int bal0, min0, bal1, min1;
    analyze(lst[0], bal0, min0);
    analyze(lst[1], bal1, min1);

    if (bal0 + bal1 != 0) return "No";
    if ((min0 >= 0 && bal0 + min1 >= 0) || (min1 >= 0 && bal1 + min0 >= 0))
        return "Yes";
    return "No";
}
