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

    for (const string& s : lst) {
        int sum = 0;
        for (char c : s) {
            int d = c - '0';
            if ((unsigned)d < 10u && (d & 1)) {
                ++sum;
            }
        }

        string num = to_string(sum);
        string res;
        res.reserve(p0.size() + p1.size() + p2.size() + p3.size() + p4.size() + num.size() * 4);

        res += p0;
        res += num;
        res += p1;
        res += num;
        res += p2;
        res += num;
        res += p3;
        res += num;
        res += p4;

        out.push_back(std::move(res));
    }

    return out;
}
