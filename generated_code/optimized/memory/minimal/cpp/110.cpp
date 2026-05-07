#include <vector>
#include <string>

using namespace std;

string exchange(vector<int> lst1, vector<int> lst2) {
    size_t remaining = lst1.size();

    for (size_t i = 0; i < lst1.size(); ++i) {
        if ((lst1[i] & 1) == 0 && remaining-- == 1) return "YES";
    }

    for (size_t i = 0; i < lst2.size(); ++i) {
        if ((lst2[i] & 1) == 0 && remaining-- == 1) return "YES";
    }

    return "NO";
}
