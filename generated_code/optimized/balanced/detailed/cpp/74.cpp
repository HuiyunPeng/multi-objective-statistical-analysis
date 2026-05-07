#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> total_match(vector<string> lst1, vector<string> lst2) {
    size_t num1 = 0, num2 = 0;

    for (const string& s : lst1) num1 += s.size();
    for (const string& s : lst2) num2 += s.size();

    return (num1 > num2) ? std::move(lst2) : std::move(lst1);
}
