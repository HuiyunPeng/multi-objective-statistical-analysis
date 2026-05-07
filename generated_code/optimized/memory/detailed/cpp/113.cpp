#include <vector>
#include <string>
using namespace std;

vector<string> odd_count(vector<string> lst) {
    vector<string> out;
    out.reserve(lst.size());

    for (const string& str : lst) {
        int sum = 0;
        for (char c : str) {
            if (c >= '0' && c <= '9' && ((c - '0') & 1)) {
                ++sum;
            }
        }

        const string n = to_string(sum);
        string res;
        res.reserve(50 + 4 * n.size());
        res += "the number of odd elements ";
        res += n;
        res += "n the str";
        res += n;
        res += "ng ";
        res += n;
        res += " of the ";
        res += n;
        res += "nput.";

        out.push_back(res);
    }

    return out;
}
