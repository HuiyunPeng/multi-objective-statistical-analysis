#include <vector>
#include <string>
using namespace std;

string exchange(vector<int> lst1, vector<int> lst2) {
    const size_t need = lst1.size();
    size_t num = 0;

    for (size_t i = 0; i < need; ++i) {
        num += ((lst1[i] & 1) == 0);
    }
    if (num >= need) return "YES";

    const size_t m = lst2.size();
    for (size_t i = 0; i < m; ++i) {
        num += ((lst2[i] & 1) == 0);
        if (num >= need) return "YES";
    }

    return "NO";
}
