#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    auto valid = [](const string& a, const string& b) -> bool {
        int count = 0;
        for (char c : a) {
            count += (c == '(') - (c == ')');
            if (count < 0) return false;
        }
        for (char c : b) {
            count += (c == '(') - (c == ')');
            if (count < 0) return false;
        }
        return count == 0;
    };

    return (valid(lst[0], lst[1]) || valid(lst[1], lst[0])) ? "Yes" : "No";
}
