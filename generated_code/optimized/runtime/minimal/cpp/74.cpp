#include <vector>
#include <string>
using namespace std;

vector<string> total_match(vector<string> lst1, vector<string> lst2) {
    size_t num1 = 0;
    for (const string& s : lst1) num1 += s.size();

    size_t num2 = 0;
    for (const string& s : lst2) {
        num2 += s.size();
        if (num2 > num1) return lst1;
    }

    return (num1 > num2) ? lst2 : lst1;
}
