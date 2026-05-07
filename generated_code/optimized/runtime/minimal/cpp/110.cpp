#include <vector>
#include <string>
using namespace std;

string exchange(vector<int> lst1, vector<int> lst2) {
    const size_t needed = lst1.size();
    if (needed == 0) return "YES";

    size_t count = 0;

    for (size_t i = 0; i < lst1.size(); ++i) {
        if (lst1[i] % 2 == 0 && ++count >= needed) return "YES";
    }

    for (size_t i = 0; i < lst2.size(); ++i) {
        if (lst2[i] % 2 == 0 && ++count >= needed) return "YES";
    }

    return "NO";
}
