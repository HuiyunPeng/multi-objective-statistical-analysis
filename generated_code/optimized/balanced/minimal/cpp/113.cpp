#include <vector>
#include <string>
using namespace std;

vector<string> odd_count(vector<string> lst) {
    static const string p0 = "the number of odd elements ";
    static const string p1 = "n the str";
    static const string p2 = "ng ";
    static const string p3 = " of the ";
    static const string p4 = "nput.";

    vector<string> out;
    out.reserve(lst.size());

    for (const string& str : lst) {
        int sum = 0;
        for (char ch : str) {
            if (ch >= '0' && ch <= '9' && ((ch - '0') & 1)) {
                ++sum;
            }
        }

        const string num = to_string(sum);
        out.emplace_back();
        string& s = out.back();
        s.reserve(p0.size() + p1.size() + p2.size() + p3.size() + p4.size() + 4 * num.size());

        s += p0;
        s += num;
        s += p1;
        s += num;
        s += p2;
        s += num;
        s += p3;
        s += num;
        s += p4;
    }

    return out;
}
