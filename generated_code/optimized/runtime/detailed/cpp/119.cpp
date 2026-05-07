#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    const string& a = lst[0];
    const string& b = lst[1];

    auto analyze = [](const string& s, int& balance, int& minPrefix) {
        int cur = 0;
        int mn = 0;
        for (char c : s) {
            if (c == '(') {
                ++cur;
            } else if (c == ')') {
                --cur;
            }
            if (cur < mn) mn = cur;
        }
        balance = cur;
        minPrefix = mn;
    };

    int balA, minA, balB, minB;
    analyze(a, balA, minA);
    analyze(b, balB, minB);

    if (balA + balB != 0) return "No";

    if (minA >= 0 && balA + minB >= 0) return "Yes";
    if (minB >= 0 && balB + minA >= 0) return "Yes";

    return "No";
}
