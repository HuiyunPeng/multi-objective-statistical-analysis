#include <vector>
#include <algorithm>
using namespace std;

vector<int> unique(vector<int> l) {
    sort(l.begin(), l.end());
    l.erase(std::unique(l.begin(), l.end()), l.end());
    return l;
}
