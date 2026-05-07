#include <vector>
#include <string>

using namespace std;

vector<string> total_match(vector<string> lst1, vector<string> lst2) {
    size_t total1 = 0;
    for (const string& s : lst1) {
        total1 += s.size();
    }

    size_t total2 = 0;
    for (const string& s : lst2) {
        total2 += s.size();
        if (total2 >= total1) {
            return lst1;
        }
    }

    return lst2;
}
