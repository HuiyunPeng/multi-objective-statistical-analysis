#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    const string& a = lst[0];
    const string& b = lst[1];

    auto analyze = [](const string& s, int& total, int& min_prefix) {
        int balance = 0;
        int min_bal = 0;
        for (char c : s) {
            if (c == '(') {
                ++balance;
            } else if (c == ')') {
                --balance;
            }
            if (balance < min_bal) min_bal = balance;
        }
        total = balance;
        min_prefix = min_bal;
    };

    int total_a, min_a, total_b, min_b;
    analyze(a, total_a, min_a);
    analyze(b, total_b, min_b);

    if (total_a + total_b != 0) return "No";

    if (min_a >= 0 && total_a + min_b >= 0) return "Yes";
    if (min_b >= 0 && total_b + min_a >= 0) return "Yes";

    return "No";
}
