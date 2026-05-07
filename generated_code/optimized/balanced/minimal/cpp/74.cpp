#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> total_match(vector<string> lst1, vector<string> lst2) {
    if (lst1.size() <= lst2.size()) {
        size_t num1 = 0;
        for (const string& s : lst1) {
            num1 += s.size();
        }

        size_t num2 = 0;
        for (const string& s : lst2) {
            num2 += s.size();
            if (num2 >= num1) {
                return std::move(lst1);
            }
        }

        return (num1 > num2) ? std::move(lst2) : std::move(lst1);
    } else {
        size_t num2 = 0;
        for (const string& s : lst2) {
            num2 += s.size();
        }

        size_t num1 = 0;
        for (const string& s : lst1) {
            num1 += s.size();
            if (num1 > num2) {
                return std::move(lst2);
            }
        }

        return std::move(lst1);
    }
}
