#include <vector>
#include <string>
using namespace std;

string exchange(vector<int> lst1, vector<int> lst2) {
    const size_t n1 = lst1.size();
    size_t even1 = 0;

    for (size_t i = 0; i < n1; ++i) {
        even1 += ((lst1[i] & 1) == 0);
    }

    if (even1 >= n1) {
        return "YES";
    }

    size_t neededFromLst2 = n1 - even1;
    const size_t n2 = lst2.size();

    for (size_t i = 0; i < n2; ++i) {
        neededFromLst2 -= ((lst2[i] & 1) == 0);
        if (neededFromLst2 == 0) {
            return "YES";
        }
    }

    return "NO";
}
