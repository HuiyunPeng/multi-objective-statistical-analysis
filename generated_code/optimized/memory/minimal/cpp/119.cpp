#include <string>
#include <vector>
using namespace std;

string match_parens(vector<string> lst) {
    auto valid_concat = [](const string& a, const string& b) -> bool {
        int count = 0;
        for (char c : a) {
            if (c == '(') ++count;
            else if (c == ')') --count;
            if (count < 0) return false;
        }
        for (char c : b) {
            if (c == '(') ++count;
            else if (c == ')') --count;
            if (count < 0) return false;
        }
        return count == 0;
    };

    return (valid_concat(lst[0], lst[1]) || valid_concat(lst[1], lst[0])) ? "Yes" : "No";
}
