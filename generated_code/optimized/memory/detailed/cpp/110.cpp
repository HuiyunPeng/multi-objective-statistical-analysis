#include <vector>
#include <string>
using namespace std;

string exchange(vector<int> lst1, vector<int> lst2) {
    size_t need = lst1.size();
    if (need == 0) return "YES";

    for (int v : lst1) {
        if ((v & 1) == 0 && --need == 0) return "YES";
    }
    for (int v : lst2) {
        if ((v & 1) == 0 && --need == 0) return "YES";
    }

    return "NO";
}
